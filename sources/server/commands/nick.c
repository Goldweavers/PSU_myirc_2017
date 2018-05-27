/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>

#include "server.h"
#include "reply_codes.h"

static bool is_special(char c)
{
	const char *specials = "-[]\\`^{}";

	for (int i = 0; specials[i]; ++i) {
		if (specials[i] == c)
			return true;
	}
	return false;
}

static bool is_valid_nickname(char *name)
{
	for (int i = 0; name[i]; ++i) {
		if (!isalnum(name[i]) && !is_special(name[i])) {
			return false;
		}
	}
	return !isdigit(name[0]);
}

static int welcome_messages(user_t *user, char *nick)
{
	socket_t client = user->net.socket;

	user->nickname = nick;
	send_response(client, RPL_WELCOME, nick);
	send_response(client, RPL_YOURHOST, SERVERNAME, IRC_VERSION);
	send_response(client, RPL_CREATED, server.created);
	send_response(client, RPL_LUSERCHANNELS, count_nodes(server.channels));
	send_response(client, RPL_LUSERME, count_nodes(server.users));
	return EXIT_SUCCESS;
}

static bool send_nick(user_t *curr, user_t *user, char *name)
{
	const char *nickname = user ? user->nickname : curr->nickname;

	if (user == curr)
		return false;
	dprintf(curr->net.socket, ":%s NICK :%s\r\n", nickname, name);
	return true;
}

static int broadcast_to_channels(user_t *user, char *name)
{
	node_t *channel = user->channels;
	node_t *users = NULL;

	send_nick(user, NULL, name);
	for (; channel != NULL; channel = channel->next) {
		users = ((channel_t *)channel->data)->users;
		for (node_t *node = users; node != NULL; node = node->next) {
			send_nick((user_t *)node->data, user, name);
		}
	}
	free(user->nickname);
	user->nickname = name;
	return EXIT_SUCCESS;
}

int nick(char *parameters[], socket_t client)
{
	user_t *user = find_user_by_socket(server.users, client);
	char *nickname = implode(parameters);

	if (strtab_len(parameters) == 0) {
		free(nickname);
		return send_response(client, ERR_NONICKNAMEGIVEN);
	}
	if (is_valid_nickname(nickname) == false)
		send_response(client, ERR_ERRONEUSNICKNAME, nickname);
	else if (find_user_by_name(server.users, nickname) != NULL)
		send_response(client, ERR_NICKNAMEINUSE, nickname);
	else {
		if (user->nickname == NULL)
			return welcome_messages(user, nickname);
		return broadcast_to_channels(user, nickname);
	}
	free(nickname);
	return EXIT_SUCCESS;
}