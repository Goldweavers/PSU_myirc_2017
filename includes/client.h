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

#ifndef MAX_EVENTS
	#define MAX_EVENTS (128)
#endif

#ifndef MAX_USERS
	#define MAX_USERS (1024)
#endif

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

typedef struct uchannel uchannel_t;
typedef struct user user_t;

typedef struct cinfo {
	user_t my;
	socket_t listener;
	node_t *users; // user_t
	int epoll;
} cinfo_t;

typedef struct channel {
	node_t *users; // user_t
	char *name;
} channel_t;

struct user {
	char *nickname;
	node_t *publics; // channel_t
	node_t *privates; // uchannel_t
};

struct uchannel {
	socket_t client;
	char *name;
};

bool find_client_commands(char *name, command_ptr *function);

#endif //PSU_MYIRC_2017_CLIENT_H
