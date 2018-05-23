/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <sys/epoll.h>
#include <unistd.h>
#include <stdbool.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
	int epoll = epoll_create1(0);
	struct epoll_event events[128];
	struct epoll_event event = {
		.events=EPOLLIN, .data.fd=STDIN_FILENO
	};

	epoll_ctl(epoll, EPOLL_CTL_ADD, STDIN_FILENO, &event);
	while (true) {
		int nevents = epoll_wait(epoll, events, 128, -1);
		for (int i = 0; i < nevents; ++i) {
			char *line = NULL;
			size_t size = 0;

			if (events[i].events & EPOLLIN) {
				if (getline(&line, &size, stdin) > 0) {
					printf("inputs: [%s]\n", line);
					free(line);
					line = NULL;
				}
			}
		}
	}
	return 0;
}