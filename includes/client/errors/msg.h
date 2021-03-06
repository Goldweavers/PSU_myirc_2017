/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/
#ifndef PSU_MYIRC_2017_MSG_H
#define PSU_MYIRC_2017_MSG_H

enum ERROR_CODES {
	RPL_AWAY = 301,
	ERR_NOSUCHNICK = 401,
	ERR_CANNOTSENDTOCHAN = 404,
	ERR_TOOMANYTARGETS = 407,
	ERR_NORECIPIENT = 411,
	ERR_NOTEXTTOSEND = 412,
	ERR_NOTOPLEVEL = 413,
	ERR_WILDTOPLEVEL = 414
};

#endif //PSU_MYIRC_2017_MSG_H
