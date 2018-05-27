/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

#include "server.h"

static bool send_quit(user_t *curr, user_t *user, char *message)
{
	const char *format = ":%s QUIT :Self-Quit: %s\r\n";
	char *nickname = user ? user->nickname : curr->nickname;
	char *msg = strlen(message) > 0 ? message : SERVERNAME;
	socket_t client = curr->net.socket;

	if (curr == user)
		return false;
	dprintf(client, format, nickname, msg);
	return true;
}

static void broadcast_to_channels(user_t *user, char *message)
{
	node_t *channel = user->channels;
	node_t *users = NULL;

	send_quit(user, NULL, message);
	for (; channel != NULL; channel = channel->next) {
		users = ((channel_t *)channel->data)->users;
		for (node_t *node = users; node != NULL; node = node->next) {
			send_quit((user_t *)node->data, user, message);
		}
	}
}

int quit(char *parameters[], socket_t client)
{
	user_t *user = find_user_by_socket(server.users, client);
	char *message = implode(parameters);

	broadcast_to_channels(user, message);
	delete_user(user);
	free(message);
	return EXIT_SUCCESS;
}