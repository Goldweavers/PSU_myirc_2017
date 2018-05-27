/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdlib.h>
#include <memory.h>

#include "reply_codes.h"
#include "server.h"

static void reply_to_client(socket_t client, char *chan_name)
{
	channel_t *channel = find_channel_by_name(server.channels, chan_name);
	int users = 0;

	if (channel != NULL) {
		users = count_nodes(channel->users);
		send_response(client, RPL_LIST, channel->name, users);
	}
}

static int specific_channels(socket_t client, const char *names)
{
	char **strtab = str_to_strtab((char *)names, ",");

	if (!strtab)
		return EXIT_FAILURE;
	for (int i = 0; strtab[i] != NULL; ++i)
		reply_to_client(client, strtab[i]);
	free(strtab);
	return EXIT_SUCCESS;
}

static int all_channels(socket_t client)
{
	node_t *channel = server.channels;

	for (; channel != NULL; channel = channel->next)
		reply_to_client(client, ((channel_t *)channel->data)->name);
	return EXIT_SUCCESS;
}

int list(char *parameters[], socket_t client)
{
	const char *names = parameters[0];

	send_response(client, RPL_LISTSTART);
	if (strtab_len(parameters) > 0)
		specific_channels(client, names);
	else
		all_channels(client);
	send_response(client, RPL_LISTEND);
	return EXIT_SUCCESS;
}