/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <memory.h>

#include "client.h"

bool find_client_commands(char *name, command_ptr *function)
{
	const command_t commands[] = {
		{"/server", &server}, {"/nick", NULL}, {"/list", NULL},
		{"/join", NULL}, {"/part", NULL}, {"/users", NULL},
		{"/names", NULL}, {"/msg", &msg}, {"/accept_file", NULL},
		{NULL, NULL}
	};

	return find_command_by_name(name, commands, function);
}