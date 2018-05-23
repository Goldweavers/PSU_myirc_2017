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
#include <netdb.h>
#include <errno.h>

int main(int ac, char *av[])
{
	int epoll = epoll_create1(0);
	struct epoll_event events[128];
	struct protoent *protocol = getprotobyname("TCP");
	int listener = socket(AF_INET, SOCK_STREAM, protocol->p_proto);
	if (listener == -1)
		return printf("SOCKET\n");
	int opts = SO_REUSEADDR | SO_REUSEPORT;
	struct sockaddr_in in = {
		.sin_family=AF_INET, .sin_port=htons(6666),
		.sin_addr.s_addr=htonl(INADDR_ANY)
	};
	int reuse = 1;

	setsockopt(listener, SOL_SOCKET, opts, &reuse, sizeof(reuse));
	if (bind(listener, (const struct sockaddr *)&in, sizeof(in)) < 0)
		return printf("BIND\n");
	if (listen(listener, 128) < 0)
		return printf("LISTEN\n");
	struct epoll_event event = { .events=EPOLLIN, .data.fd=listener };
	epoll_ctl(epoll, EPOLL_CTL_ADD, listener, &event);
	char *line = NULL;
	size_t size = 0;
	while (true) {
		printf("EPOLL_WAIT\n");
		int nevents = epoll_wait(epoll, events, 128, -1);
		for (int i = 0; i < nevents; ++i) {
			if (events[i].events & EPOLLERR || events[i].events & EPOLLHUP) {
				epoll_ctl(epoll, EPOLL_CTL_DEL, events[i].data.fd, &events[i]);
				close(events[i].data.fd);
				printf("ERRORED FD DETECTED AND REMOVED\n");
			} else if (events[i].events & EPOLLIN) {
				if (events[i].data.fd == listener) {
					printf("BEGIN LISTENER\n");
					struct sockaddr_in in1;
					socklen_t socklen = sizeof(in1);
					int client = accept(events[i].data.fd, (struct sockaddr *)&in1, &socklen);
					struct epoll_event ev = { .events=EPOLLIN, .data.fd=client };
					epoll_ctl(epoll, EPOLL_CTL_ADD, client, &ev);
				} else {
					if (getline(&line, &size, fdopen(events[i].data.fd, "r")) == -1) {
						epoll_ctl(epoll, EPOLL_CTL_DEL, events[i].data.fd, &events[i]);
						close(events[i].data.fd);
					}
					free(line);
					size = 0;
					line = NULL;
				}
			}
		}
		printf("END LOOP\n");
		sleep(2);
	}
	return 0;
}