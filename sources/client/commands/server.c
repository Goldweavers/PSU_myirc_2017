/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdlib.h>

#include "client.h"

#include <unistd.h>
#include <memory.h>
#include <arpa/inet.h>
#include <stdio.h>

// TODO: really do this function
int server(char *parameters[], socket_t server)
{
	socket_t sock;
	in_port_t port;

	(void)server;
	if (strlen(parameters[0]) == 0)
		return eprintf(-1, "Not enough parameters given\n");
	struct sockaddr_in sa;
	char str[INET_ADDRSTRLEN];

	// store this IP address in sa:
	inet_pton(AF_INET, parameters[0], &(sa.sin_addr));

	// now get it back and print it
	inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);

	printf("addr: %s\n", str);
	/*if (inet_pton(AF_INET, parameters[0], &(sa.sin_addr)) != 1)
		return eprintf(-1, "Invalid IP address\n");*/
	if (!socket_init("TCP", &sock))
		return -EXIT_FAILURE;
	if (!str_to_port(parameters[1], &port))
		port = 6667;
	if (socket_connect(sock, sa.sin_addr.s_addr, port) == -EXIT_FAILURE) {
		printf("err: %s\n", geterr());
		return -EXIT_FAILURE;
	}
	printf("Successfully connected\n");
	return EXIT_SUCCESS;
}
