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

int users(char *parameters[], socket_t client)
{
	node_t *user = server.users;

	(void)parameters;
	send_response(client, RPL_USERSSTART);
	if (user == NULL)
		send_response(client, RPL_NOUSERS);
	for (; user != NULL; user = user->next) {
		send_response(client, RPL_USERS,
			((user_t *)user->data)->nickname,
			"<ttyline>", "<hostname>");
	}
	send_response(client, RPL_ENDOFUSERS);
	return EXIT_SUCCESS;
}