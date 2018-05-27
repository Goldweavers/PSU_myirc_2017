/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stddef.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <memory.h>
#include <time.h>

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

static int server_init(in_port_t port)
{
	time_t now = time(NULL);
	struct tm *time = localtime(&now);

	server.created = asctime(time);
	eprintf(0, "Created on %s", server.created);
	server.created[strlen(server.created) - 1] = '\0';
	if (!epoll_init(&server.epoll) || !listener_init(port))
		return EPITECH_ERROR;
	while (true)
		wait_for_events();
}

int main(int ac, char *av[])
{
	in_port_t port;

	(void)ac;
	signal(SIGINT, &sig_handler);
	if (av[1] && !strcmp(av[1], "-help"))
		return print_usage(EXIT_SUCCESS);
	if (str_to_port(av[1], &port) == false)
		return eprintf(EPITECH_ERROR, "Invalid port\n");
	return server_init(port);
}