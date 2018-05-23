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
	#define MAX_EVENTS 128
#endif

#ifndef MAX_USERS
	#define MAX_USERS 1024
#endif

typedef struct user user_t;
typedef struct channel channel_t;

typedef struct server {
	node_t *users; // user_t
	socket_t listener;
	node_t *channels; // channel_t
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

#endif //PSU_MYIRC_2017_SERVER_H
