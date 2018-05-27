/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
**
*/

#include <stdlib.h>
#include <stdio.h>

#include "client/errors/msg.h"
#include "client.h"

int part(char *parameters[], socket_t server)
{
	dprintf(server, "PART %s\r\n", implode(parameters));
	return EXIT_SUCCESS;
}
