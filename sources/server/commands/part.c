/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdlib.h>

#include "reply_codes.h"
#include "server.h"

static int handle_part(user_t *user, const char *name)
{
	channel_t *channel = find_channel_by_name(server.channels, name);

	if (channel == NULL)
		return send_response(user->net.socket, ERR_NOSUCHCHANNEL,
			name, "No such channel");
	if (!find_user_by_name(channel->users, user->nickname))
		return send_response(user->net.socket, ERR_NOTONCHANNEL,
			channel->name);
	delete_node(&user->channels, (void *)channel);
	broadcast_leave_to_users(channel->users, channel->name, user->nickname);
	if (count_nodes(channel->users) > 1)
		delete_node(&channel->users, (void *)user);
	else
		delete_channel(channel);
	return EXIT_SUCCESS;
}

int part(char *parameters[], socket_t client)
{
	user_t *user = find_user_by_socket(server.users, client);
	char **channels = NULL;

	if (strtab_len(parameters) == 0)
		return send_response(client, ERR_NEEDMOREPARAMS,
			"PART", "Not enough parameters.");
	channels = str_to_strtab(parameters[0], ",");
	for (int i = 0; channels[i]; ++i)
		handle_part(user, channels[i]);
	free(channels);
	return EXIT_SUCCESS;
}