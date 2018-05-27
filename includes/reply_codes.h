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

	RPL_LUSERCHANNELS	=	254,
	RPL_LUSERME		=	255,

	RPL_LISTSTART		=	321,
	RPL_LIST		=	322,
	RPL_LISTEND		=	323,
	RPL_NAMREPLY		=	353,
	RPL_ENDOFNAMES		=	366,

	RPL_USERSSTART		=	392,
	RPL_USERS		=	393,
	RPL_ENDOFUSERS		=	394,
	RPL_NOUSERS		=	395,

	ERR_NOSUCHCHANNEL	=	403,

	ERR_NONICKNAMEGIVEN	=	431,
	ERR_ERRONEUSNICKNAME	=	432,
	ERR_NICKNAMEINUSE	=	433,

	ERR_NOTONCHANNEL	=	442,
	ERR_USERONCHANNEL	=	443,

	ERR_NOTREGISTERED	=	451,

	ERR_NEEDMOREPARAMS	=	461,
};

typedef struct reply {
	enum reply_code code;
	char *message;
} reply_t;

bool send_response(socket_t client, enum reply_code code, ...);

#endif //PSU_MYIRC_2017_REPLY_CODES_H
