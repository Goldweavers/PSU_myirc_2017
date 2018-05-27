/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
**
*/

#include <stdio.h>
#include <stdlib.h>
#include "client.h"

int join(char *parameters[], socket_t server)
{
	dprintf(server, "JOIN %s\r\n", implode(parameters));
	return EXIT_SUCCESS;
}
