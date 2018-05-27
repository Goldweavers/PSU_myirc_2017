/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include "reply_codes.h"
#include "server.h"

static char *implodes(node_t *users)
{
	char *result = NULL;
	char *nickname = NULL;
	size_t user_len = 0;
	size_t len = 1;

	for (node_t *user = users; user != NULL; user = user->next) {
		nickname = ((user_t *)user->data)->nickname;
		if (!nickname)
			continue;
		user_len = strlen(nickname) + 1;
		result = realloc(result, len + user_len);
		if (!result)
			return NULL;
		sprintf(&result[len - 1], "%s%c",
			nickname, user->next ? ' ' : '\0');
		len += user_len;
	}
	return result;
}

static bool reply_to_client(socket_t client, char *name)
{
	channel_t *channel = find_channel_by_name(server.channels, name);
	char *users = NULL;

	if (channel != NULL) {
		users = implodes(channel->users);
		if (!users)
			return false;
		send_response(client, RPL_NAMREPLY, channel->name, users);
		free(users);
		return send_response(client, RPL_ENDOFNAMES, channel->name);
	}
	return !send_response(client, ERR_NOSUCHCHANNEL,
		name, "No such channel");
}

int names(char *parameters[], socket_t client)
{
	char **strtab = NULL;

	if (strtab_len(parameters) > 0) {
		strtab = str_to_strtab(parameters[0], ",");
		if (strtab == NULL)
			return EXIT_FAILURE;
		for (int i = 0; strtab[i] != NULL; ++i)
			reply_to_client(client, strtab[i]);
		free(strtab);
		return EXIT_SUCCESS;
	}
	return !send_response(client, RPL_ENDOFNAMES, "*");
}