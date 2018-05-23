/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <sys/epoll.h>
#include <stdlib.h>

#include "common.h"

bool epoll_init(int *epfd)
{
	*epfd = epoll_create1(0);

	if (*epfd == -EXIT_FAILURE)
		return eprintf(false, "epoll: %s\n", geterr());
	return true;
}

bool epoll_push(int epfd, socket_t to_watch, uint32_t events)
{
	const int opcodes = EPOLL_CTL_ADD;
	struct epoll_event event = {
		.events=events, .data.fd=to_watch
	};

	if (epoll_ctl(epfd, opcodes, to_watch, &event) == -EXIT_FAILURE)
		return eprintf(false, "epoll add: %s\n", geterr());
	return true;
}

bool epoll_pop(int epfd, socket_t to_del)
{
	const int opcodes = EPOLL_CTL_DEL;
	struct epoll_event event;

	if (epoll_ctl(epfd, opcodes, to_del, &event) == -EXIT_FAILURE)
		return eprintf(false, "epoll pop: %s\n", geterr());
	return true;
}