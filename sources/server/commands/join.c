/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdlib.h>
#include <memory.h>
#include <time.h>

#include "reply_codes.h"
#include "server.h"

static channel_t *create_channel(char *name)
{
	time_t now = time(NULL);
	channel_t channel = { .name=name, .users=NULL };
	struct tm *time = localtime(&now);

	channel.created = asctime(time);
	eprintf(0, "Creating channel %s: %s\n", channel.name, geterr());
	push_front(&server.channels, &channel, sizeof(channel));
	return server.channels->data;
}

static bool is_valid_name(char *name)
{
	if (name[0] != '#' || strlen(name) > 200) {
		free(name);
		return false;
	}
	return true;
}

static int handle_channel(user_t *user, char *name)
{
	channel_t channel = { .name=strdup(name), .users=NULL };
	channel_t *to_join = find_channel_by_name(server.channels, name);
	char *parameters[] = { name, NULL };

	if (!is_valid_name(channel.name))
		return send_response(user->net.socket, ERR_NOSUCHCHANNEL,
			channel.name, "Invalid channel name");
	if (to_join == NULL)
		to_join = create_channel(channel.name);
	else
		free(channel.name);
	if (user->nickname && find_user_by_name(to_join->users, user->nickname))
		return send_response(user->net.socket, ERR_USERONCHANNEL,
			user->nickname, to_join->name);
	push_front(&user->channels, to_join, 0);
	push_front(&to_join->users, user, 0);
	broadcast_join_to_users(to_join->users, to_join->name, user->nickname);
	return names(parameters, user->net.socket);
}

int join(char *parameters[], socket_t client)
{
	user_t *user = find_user_by_socket(server.users, client);
	char **channels = NULL;

	if (!strtab_len(parameters))
		return send_response(client, ERR_NEEDMOREPARAMS,
			"JOIN", "Please specify a channel");
	channels = str_to_strtab(parameters[0], ",");
	for (int i = 0; channels[i]; ++i)
		handle_channel(user, channels[i]);
	free(channels);
	return EXIT_SUCCESS;
}