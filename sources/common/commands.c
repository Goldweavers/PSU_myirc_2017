/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <memory.h>

#include "common.h"

bool find_command_by_name(char *name, \
const command_t *commands, command_ptr *function)
{
	int i = 0;

	for (; commands[i].name != NULL; ++i) {
		if (strcmp(commands[i].name, name) == 0) {
			*function = commands[i].function;
			return true;
		}
	}
	return false;
}