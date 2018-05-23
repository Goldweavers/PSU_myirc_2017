/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stddef.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "client.h"

int client(void)
{
	char *line = NULL;
	command_ptr function;
	size_t size = 0;
	char **strtab;

	while (printf("[(status)] ") && getline(&line, &size, stdin) > 0) {
		strtab = str_to_strtab(line);
		// TODO: check strtab calloc
		if (find_client_commands(strtab[0], &function) == false) {
			eprintf(0, "Unknown command: %s\n", &strtab[0][1]);
		} else
			function(&strtab[1]);
		freeset((void **)&line);
		free(strtab);
	}
	return EXIT_SUCCESS;
}

int main(int ac, char *av[])
{
	const char error[] = "Too many argument: %d > 0.\n";

	(void)av;
	if (ac > 1)
		return eprintf(EPITECH_ERROR, error, ac - 1);
	printf("    __  ___      ________  ______\n"
	       "   /  |/  /_  __/  _/ __ \\/ ____/\n"
	       "  / /|_/ / / / // // /_/ / /     \n"
	       " / /  / / /_/ // // _, _/ /___   \n"
	       "/_/  /_/\\__, /___/_/ |_|\\____/   \n"
	       "       /____/                    \n\n");
	return client();
}