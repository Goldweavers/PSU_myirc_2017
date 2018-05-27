/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdlib.h>
#include <unistd.h>

#include "server.h"

void sig_handler(int status)
{
	node_t *next = NULL;

	(void)status;
	close(server.epoll);
	close(server.listener);
	eprintf(0, "Exiting server...\n");
	for (node_t *node = server.users; node != NULL; node = next) {
		next = node->next;
		delete_user((user_t *)node->data);
	}
	for (node_t *node = server.channels; node != NULL; node = next) {
		next = node->next;
		delete_channel((channel_t *)node->data);
	}
	free(server.created);
	exit(EXIT_SUCCESS);
}