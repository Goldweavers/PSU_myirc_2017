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

// TODO: really do this function
int server(char *parameters[])
{
	socket_t sock;

	socket_init("TCP", &sock);
	if (sock == -EXIT_FAILURE
		|| socket_connect(sock, INADDR_LOOPBACK, 6665) == -1)
		return EXIT_FAILURE;

	const char str[] = "Message from client.\n";
	write(sock, str, strlen(str));

	char buffer[1024];
	memset(buffer, '\0', 1024);
	read(sock, buffer, 1024 - 1);
	write(STDOUT_FILENO, buffer, strlen(buffer));
	return EXIT_SUCCESS;
}