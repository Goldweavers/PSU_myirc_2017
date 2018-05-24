/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/
#ifndef PSU_MYIRC_2017_SERVER_H
#define PSU_MYIRC_2017_SERVER_H

#include "common.h"

#ifndef MAX_EVENTS
	#define MAX_EVENTS (128)
#endif

#ifndef MAX_USERS
	#define MAX_USERS (1024)
#endif

#ifndef SERVERNAME
	#define SERVERNAME ("MyIRC")
#endif

#ifndef IRC_VERSION
	#define IRC_VERSION (0.1)
#endif

typedef struct user user_t;
typedef struct channel channel_t;

typedef struct server {
	node_t *users; // user_t
	socket_t listener;
	node_t *channels; // channel_t
	struct tm *creation;
	int epoll;
} server_t;

struct user {
	char *nickname;
	node_t *channels; // channel_t
	client_t net;
};

struct channel {
	node_t *users; // user_t
	char *name;
};

extern server_t server;

/* user.c */
user_t *find_user_by_socket(node_t *users, socket_t client);

user_t *find_user_by_name(node_t *users, const char *nickname);
/* !user.c */

/* commands */
int nick(char *parameters[], socket_t client);
/* !commands */

#endif //PSU_MYIRC_2017_SERVER_H
