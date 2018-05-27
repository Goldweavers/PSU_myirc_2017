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

static bool is_valid_nickname(const char *name)
{
	for (int i = 0; name[i]; ++i) {
		if (!isalnum(name[i]) && !is_special(name[i])) {
			return false;
		}
	}
	return !isdigit(name[0]);
}

static void welcome_messages(socket_t client, const char *nick)
{
	send_response(client, RPL_WELCOME, nick);
	send_response(client, RPL_YOURHOST, SERVERNAME, IRC_VERSION);
	send_response(client, RPL_CREATED, server.created);
	send_response(client, RPL_LUSERCHANNELS, count_nodes(server.channels));
	send_response(client, RPL_LUSERME, count_nodes(server.users));
}

int nick(char *parameters[], socket_t client)
{
	user_t *user = find_user_by_socket(server.users, client);
	const char *nick = parameters[0];

	if (strtab_len(parameters) == 0)
		return send_response(client, ERR_NONICKNAMEGIVEN);
	if (is_valid_nickname(nick) == false)
		return send_response(client, ERR_ERRONEUSNICKNAME, nick);
	if (find_user_by_name(server.users, nick) != NULL)
		return send_response(client, ERR_NICKNAMEINUSE, nick);
	if (user->nickname == NULL) {
		user->nickname = strdup(nick);
		welcome_messages(user->net.socket, nick);
		return EXIT_SUCCESS;
	}
	free(user->nickname);
	user->nickname = strdup(nick);
	return EXIT_SUCCESS;
}