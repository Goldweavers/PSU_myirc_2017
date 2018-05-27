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

static int send_to_user(socket_t client, user_t *receiver, \
char *name, char *message)
{
	user_t *sender = find_user_by_socket(server.users, client);

	if (!message || !strlen(message))
		return !send_response(client, ERR_NOTEXTTOSEND);
	dprintf(receiver->net.socket, ":%s PRIVMSG %s :%s\r\n", \
sender->nickname, name, message);
	return EXIT_SUCCESS;
}

static int private_message(socket_t client, char *name, char *message)
{
	user_t *receiver = find_user_by_name(server.users, name);

	if (receiver == NULL)
		return !send_response(client, ERR_NOSUCHNICK, name);
	return send_to_user(client, receiver, name, message);
}

static int broadcast_to_users(socket_t client, char *name, char *message)
{
	channel_t *channel = find_channel_by_name(server.channels, name);

	if (channel == NULL)
		return !send_response(client, ERR_NOSUCHNICK, name);
	for (node_t *user = channel->users; user; user = user->next)
		send_to_user(client, user->data, channel->name, message);
	return EXIT_SUCCESS;
}

int privmsg(char *parameters[], socket_t client)
{
	char **receivers = NULL;
	char *message = NULL;

	if (strtab_len(parameters) < 2)
		return send_response(client, ERR_NEEDMOREPARAMS, \
"PRIVMSG", "Not enough parameters.");
	receivers = str_to_strtab(parameters[0], ",");
	message = implode(&parameters[1]);
	if (!receivers)
		return EXIT_FAILURE;
	for (int i = 0; receivers[i]; ++i) {
		if (strncmp(receivers[i], "#", 1) == 0)
			broadcast_to_users(client, receivers[i], message);
		else
			private_message(client, receivers[i], message);
	}
	free(receivers);
	free(message);
	return EXIT_SUCCESS;
}