/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"

bool find_client_commands(char *name, command_ptr *function)
{
	const command_t commands[] = {
		{"/server", &server}, {"/nick", &nick}, {"/list", &list},
		{"/join", &join}, {"/part", &part}, {"/users", &users},
		{"/names", &names}, {"/msg", &msg}, {"/quit", &quit},
		{"/accept_file", &accept_file},
		{NULL, NULL}
	};

	return find_command_by_name(name, commands, function);
}

char *format_reply_message(char *reply)
{
	return strstr(reply + 1, ":") + 1;
}

bool fill_cinfo(char *reply)
{
	char **reply_arr = str_to_strtab(reply);
	int cmd = 3;

	if (atoi(reply_arr[1]) != 0) {
		free(reply_arr);
		return false;
	}

	if (strcmp(reply_arr[cmd], "JOIN") == 0)
		return push_front();
	if (strcmp(reply_arr[cmd]))

}



