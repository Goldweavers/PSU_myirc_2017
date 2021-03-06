/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdlib.h>
#include <stdio.h>

#include "client/errors/msg.h"
#include "client.h"

int msg(char *parameters[], socket_t server)
{
	dprintf(server, "PRIVMSG %s\r\n", implode(parameters));
	return EXIT_SUCCESS;
}
