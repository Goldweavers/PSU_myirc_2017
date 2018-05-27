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

int accept_file(char *parameters[], socket_t server)
{
	dprintf(server, "ACCEPT_FILE %s\r\n", implode(parameters));
	return EXIT_SUCCESS;
}
