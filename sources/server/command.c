/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdlib.h>
#include <stdio.h>

#include "reply_codes.h"
#include "server.h"

bool find_server_commands(char *name, command_ptr *function)
{
	const command_t commands[] = {
		{"NICK", &nick}, {"LIST", &list}, {"JOIN", &join},
		{"PART", &part}, {"USERS", &users}, {"PRIVMSG", NULL},
		{"QUIT", &quit}, {"NAMES", &names}, {NULL, NULL}
	};

	return find_command_by_name(name, commands, function);
}

static bool need_register(command_ptr *function)
{
	return *function != &nick && *function != &quit;
}

bool handle_command(socket_t client, char *command)
{
	char **arguments = str_to_strtab(command, " ");
	user_t *user = find_user_by_socket(server.users, client);
	command_ptr function;

	if (arguments == NULL)
		return eprintf(false, "Failed to allocate\n");
	if (find_server_commands(arguments[0], &function) == false)
		dprintf(client, "Unknown command: %s\n", arguments[0]);
	else if (need_register(&function) && user->nickname == NULL)
		send_response(client, ERR_NOTREGISTERED, arguments[0]);
	else
		function(&arguments[1], client);
	free(arguments);
	free(command);
	return true;
}