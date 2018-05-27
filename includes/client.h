/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/
#ifndef PSU_MYIRC_2017_CLIENT_H
#define PSU_MYIRC_2017_CLIENT_H

#include "common.h"

/* Commands */

int msg(char *parameters[], socket_t server);

int join(char *parameters[], socket_t server);

int server(char *parameters[], socket_t server);

int part(char *parameters[], socket_t server);

int nick(char *parameters[], socket_t server);

int list(char *parameters[], socket_t server);

int users(char *parameters[], socket_t server);

int names(char *parameters[], socket_t server);

int quit(char *parameters[], socket_t server);

int accept_file(char *parameters[], socket_t server);


/* !Commands */

typedef struct cinfo {
	char *nickname;
	node_t *channels;
	socket_t socket;

}cinfo_t;

/* commands.c */

char *implode(char **parameters);

/* !commands.c */

bool find_client_commands(char *name, command_ptr *function);

#endif //PSU_MYIRC_2017_CLIENT_H
