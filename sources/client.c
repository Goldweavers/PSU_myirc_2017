/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <stdlib.h>

#include "client.h"

cinfo_t client = { 0 };

static bool listener_init(in_port_t port)
{
	int conn = MAX_USERS + 1;

	if (socket_init("TCP", &client.listener) == false)
		return false;
	if (socket_bind(client.listener, INADDR_ANY, port, conn) == -1) {
		close(client.listener);
		return false;
	}
	if (epoll_push(client.epoll, client.listener, EPEVENTS) == false) {
		close(client.listener);
		close(client.epoll);
		return false;
	}
	return true;
}

static bool del_corrupted(const struct epoll_event *event)
{
	const char *format = "corrupted fd <%d> was removed\n";

	if (event->events & EPOLLERR || event->events & EPOLLHUP) {
		epoll_pop(client.epoll, event->data.fd);
		close(event->data.fd);
		return eprintf(true, format, event->data.fd);
	}
	return false;
}

user_t *find_user_by_socket(node_t *users, socket_t client)
{
	node_t *node = users;

	for (; node != NULL; node = node->next) {
		if (((user_t *)node->data)->net.socket == client)
			return (user_t *)node->data;
	}
	return NULL;
}

int wait_for_events(void)
{
	static struct epoll_event events[MAX_EVENTS];
	int nevents = epoll_wait(client.epoll, events, MAX_EVENTS, -1);
	struct epoll_event *event = events;
	user_t *user = NULL;

	for (int i = 0; i < nevents; event = &events[++i]) {
		user = find_user_by_socket(server.users, event->data.fd);
		if (!del_corrupted(event) && event->events & EPOLLRDHUP)
			delete_user(user);
		else if (event->events & EPOLLIN)
			handle_event(event);
	}
	return EXIT_SUCCESS;
}

static int client_init(void)
{
	if (epoll_init(&client.epoll) == false)
		return EPITECH_ERROR;
	if (epoll_push(client.epoll, STDIN_FILENO, EPEVENTS) == false)
		return EPITECH_ERROR;
	while (true)
		wait_for_events();
}

int main(int ac, char *av[])
{
	const char error[] = "Too many argument: %d > 0.\n";

	(void)av;
	if (ac > 1)
		return eprintf(EPITECH_ERROR, error, ac - 1);
	printf("    __  ___      ________  ______\n"
	       "   /  |/  /_  __/  _/ __ \\/ ____/\n"
	       "  / /|_/ / / / // // /_/ / /     \n"
	       " / /  / / /_/ // // _, _/ /___   \n"
	       "/_/  /_/\\__, /___/_/ |_|\\____/   \n"
	       "       /____/                    \n\n");
	return client_init();
}