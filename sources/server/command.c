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

static int debug(char *parameters[], socket_t client)
{
	(void)client;
	(void)parameters;
	return EXIT_SUCCESS;
}

bool find_server_commands(char *name, command_ptr *function)
{
	const command_t commands[] = {
		{"NICK", &nick}, {"LIST", &list}, {"JOIN", &join},
		{"PART", &part}, {"USERS", &users}, {"PRIVMSG", &debug},
		{"QUIT", &quit}, {"NAMES", &names}, {NULL, NULL}
	};

	return find_command_by_name(name, commands, function);
}

bool handle_command(socket_t client, char *input)
{
	char **strtab = str_to_strtab(input, " ");
	user_t *user = find_user_by_socket(server.users, client);
	command_ptr function;

	if (!strtab)
		return eprintf(false, "Failed to allocate\n");
	if (find_server_commands(strtab[0], &function) == false)
		dprintf(client, "Unknown command: %s\n", strtab[0]);
	else if (function != nick && user->nickname == NULL)
		send_response(client, ERR_NOTREGISTERED, strtab[0]);
	else
		function(&strtab[1], client);
	free(strtab);
	free(input);
	return true;
}