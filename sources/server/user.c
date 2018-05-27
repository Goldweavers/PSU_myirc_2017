/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

#include "server.h"

user_t *find_user_by_socket(node_t *users, socket_t client)
{
	node_t *node = users;

	for (; node != NULL; node = node->next) {
		if (((user_t *)node->data)->net.socket == client)
			return (user_t *)node->data;
	}
	return NULL;
}

user_t *find_user_by_name(node_t *users, const char *nickname)
{
	node_t *node = users;
	user_t *user;

	for (; node != NULL; node = node->next) {
		user = (user_t *)node->data;
		if (user->nickname && strcmp(user->nickname, nickname) == 0)
			return user;
	}
	return NULL;
}

int delete_user(user_t *user)
{
	if (!user)
		return EXIT_FAILURE;
	for (node_t *node = user->channels; node != NULL; node = node->next) {
		delete_node(&((channel_t *)node->data)->users, (void *)user);
	}
	delete_nodes(&user->channels);
	epoll_pop(server.epoll, user->net.socket);
	close(user->net.socket);
	free(user->nickname);
	delete_node(&server.users, (void *)user);
	return eprintf(EXIT_SUCCESS, "Exiting client: %s\n", geterr());
}