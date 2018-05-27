/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>

#include "server.h"

static bool del_corrupted(const struct epoll_event *event)
{
	const char *format = "corrupted fd <%d> was removed\n";

	if (event->events & EPOLLERR || event->events & EPOLLHUP) {
		epoll_pop(server.epoll, event->data.fd);
		close(event->data.fd);
		return eprintf(true, format, event->data.fd);
	}
	return false;
}

static bool create_new_user(void)
{
	user_t user = { .nickname=NULL, .channels=NULL };
	uint32_t events = EPOLLIN | EPOLLRDHUP;

	if (socket_accept(server.listener, &user.net)) {
		if (!epoll_push(server.epoll, user.net.socket, events))
			return !close(user.net.socket);
		if (push_front(&server.users, &user, sizeof(user)) == false) {
			epoll_pop(server.epoll, user.net.socket);
			return !close(user.net.socket);
		}
		return eprintf(true, "Accepting client: %s\n", geterr());
	}
	return false;
}

static bool get_inputs(socket_t sock, char **inputs)
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

static bool handle_event(const struct epoll_event *event)
{
	user_t *user = NULL;
	char *line = NULL;

	if (event->data.fd == server.listener)
		return create_new_user();
	if (get_inputs(event->data.fd, &line) == true) {
		user = find_user_by_socket(server.users, event->data.fd);
		if (line == NULL)
			return delete_user(user);
		return handle_command(event->data.fd, line);
	}
	return false;
}

int wait_for_events(void)
{
	static struct epoll_event events[MAX_EVENTS];
	int nevents = epoll_wait(server.epoll, events, MAX_EVENTS, -1);
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