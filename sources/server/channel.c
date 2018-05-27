/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stddef.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "server.h"

int delete_channel(channel_t *channel)
{
	delete_nodes(&channel->users);
	free(channel->name);
	delete_node(&server.channels, (void *)channel);
	return eprintf(EXIT_SUCCESS, "Removing channel: %s\n", geterr());
}

channel_t *find_channel_by_name(node_t *channels, const char *name)
{
	for (node_t *node = channels; node != NULL; node = node->next) {
		if (strcmp(((channel_t *)node->data)->name, name) == 0)
			return (channel_t *)node->data;
	}
	return NULL;
}

int broadcast_leave_to_users(node_t *users, const char *channel, char *nickname)
{
	for (node_t *user = users; user != NULL; user = user->next) {
		dprintf(((user_t *)user->data)->net.socket,
			":%s PART :%s\r\n", nickname, channel);
	}
	return EXIT_SUCCESS;
}

int broadcast_join_to_users(node_t *users, const char *channel, char *nickname)
{
	for (node_t *user = users; user != NULL; user = user->next) {
		dprintf(((user_t *)user->data)->net.socket,
			":%s JOIN :%s\r\n", nickname, channel);
	}
	return EXIT_SUCCESS;
}