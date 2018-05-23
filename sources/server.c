/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include "server.h"

server_t server = { .listener=-1, .channels=NULL, .users=NULL };

static int print_usage(int status)
{
	const char usage[] = "USAGE: ./server port\n";

	write(STDOUT_FILENO, usage, sizeof(usage));
	return status;
}

static bool listener_init(in_port_t port)
{
	int conn = MAX_USERS + 1;

	if (socket_init("TCP", &server.listener) == false)
		return false;
	if (socket_bind(server.listener, INADDR_ANY, port, conn) == -1) {
		close(server.listener);
		return false;
	}
	if (epoll_push(server.epoll, server.listener, EPOLLIN) == false) {
		close(server.listener);
		close(server.epoll);
		return false;
	}
	return true;
}

bool del_corrupted(const struct epoll_event *event)
{
	const char *format = "corrupted fd <%d> was removed\n";

	if (event->events & EPOLLERR || event->events & EPOLLHUP) {
		epoll_pop(server.epoll, event->data.fd);
		close(event->data.fd);
		return eprintf(true, format, event->data.fd);
	}
	return false;
}

user_t *find_user_by_socket(socket_t client)
{
	node_t *node = server.users;

	for (; node != NULL; node = node->next) {
		if (((user_t *)node)->net.socket == client)
			return (user_t *)node;
	}
	return NULL;
}

user_t *find_user_by_nickname(const char *nickname)
{
	node_t *node = server.users;

	for (; node != NULL; node = node->next) {
		if (((user_t *)node)->nickname == nickname)
			return (user_t *)node;
	}
	return NULL;
}

bool accept_new_user(void)
{
	user_t user = { .nickname=/*gen_nickname()*/"PUTE", .channels=NULL };
	bool epolled = true;

	if (socket_accept(server.listener, &user.net)) {
		if (!epoll_push(server.epoll, user.net.socket, EPOLLIN)) {
			write(user.net.socket, "")
			return !close(user.net.socket);
		}
		if (push_front(&server.users, &user, sizeof(user)) == false) {
			// TODO: send response to client
			epoll_pop(server.epoll, user.net.socket);
			return !close(user.net.socket);
		}
		return true;
	}
	return false;
}

bool find_server_commands(char *name, command_ptr *function)
{
	const command_t commands[] = {
		//{"/server", &server}, {"/nick", NULL}, {"/list", NULL},
		{"/join", NULL}, {"/part", NULL}, {"/users", NULL},
		//{"/names", NULL}, {"/msg", &msg}, {"/accept_file", NULL},
		{NULL, &broadcast}
	};

	return find_command_by_name(name, commands, function);
}

bool handle_command(socket_t sock, char *input)
{
	char **strtab = str_to_strtab(input);
	command_ptr function;

	if (!strtab)
		return eprintf(false, "Failed to allocate\n");
	if (find_server_commands(strtab[0], &function) == false)
		dprintf(sock, "Unknown command: %s\n", &strtab[0][1]);
	else
		function(&strtab[1]);
	free(strtab);
	free(input);
	return true;
}

bool get_inputs(socket_t sock, char **inputs)
{
	size_t size = 0;
	socket_t clone = dup(sock);
	FILE *file = NULL;

	if (clone == -EXIT_FAILURE)
		return eprintf(false, "dup: %s\n", geterr());
	file = fdopen(clone, "r");
	if (file == NULL) {
		close(clone);
		return eprintf(false, "fdopen: %s\n", geterr());
	}
	if (getline(inputs, &size, file) == -EXIT_FAILURE)
		freeset((void **)inputs);
	fclose(file);
	return true;
}

bool handle_event(const struct epoll_event *event)
{
	char *line = NULL;

	if (event->data.fd == server.listener)
		return accept_new_user();
	if (get_inputs(event->data.fd, &line) == true) {
		if (line == NULL) {
			epoll_pop(server.epoll, event->data.fd);
			close(event->data.fd);
			return eprintf(true, "Exiting client: %s\n", geterr());
		}
		return handle_command(event->data.fd, line);
	}
	return false;
}

int wait_for_events(void)
{
	static struct epoll_event events[MAX_EVENTS];
	int nevents = epoll_wait(server.epoll, events, MAX_EVENTS, -1);
	struct epoll_event *event = events;

	for (int i = 0; i < nevents; event = &events[++i]) {
		if (!del_corrupted(event) && event->events & EPOLLIN) {
			handle_event(event);
		}
	}
	return EXIT_SUCCESS;
}

static int server_init(in_port_t port)
{
	if (!epoll_init(&server.epoll) || !listener_init(port))
		return EPITECH_ERROR;
	while (true)
		wait_for_events();
}

void sighandler(int status)
{
	node_t *next = NULL;

	(void)status;
	close(server.epoll);
	close(server.listener);
	for (node_t *node = server.users; node != NULL; node = next) {
		close(((user_t *)node->data)->net.socket);
		next = node->next;
		free(node);
	}
	for (node_t *node = server.channels; node != NULL; node = next) {
		next = node->next;
		free(node);
	}
	exit(EXIT_SUCCESS);
}

int main(int ac, char *av[])
{
	in_port_t port;

	signal(SIGINT, &sighandler);
	if (av[1] && !strcmp(av[1], "-help"))
		return print_usage(EXIT_SUCCESS);
	if (str_to_port(av[1], &port) == false)
		return eprintf(EPITECH_ERROR, "Invalid port\n");
	return server_init(port);
}