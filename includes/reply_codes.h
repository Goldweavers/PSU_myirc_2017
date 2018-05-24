/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/
#ifndef PSU_MYIRC_2017_REPLY_CODES_H
#define PSU_MYIRC_2017_REPLY_CODES_H

#include "common.h"

enum reply_code {
	RPL_WELCOME		=	1,
	RPL_YOURHOST		=	2,
	RPL_CREATED		=	3,

	ERR_NONICKNAMEGIVEN	=	431,
	ERR_ERRONEUSNICKNAME	=	432,
	ERR_NICKNAMEINUSE	=	433,
};

typedef struct reply {
	enum reply_code code;
	char *message;
} reply_t;

bool send_response(socket_t client, enum reply_code code, ...);

#endif //PSU_MYIRC_2017_REPLY_CODES_H
