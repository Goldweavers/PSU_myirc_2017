/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include <malloc.h>

#include "reply_codes.h"

const reply_t replies[] = {
	{RPL_WELCOME, "Welcome to the Internet Relay Network"},
	/**
	 * %s: servername
	 * %f: version
	 */
	{RPL_YOURHOST, "Your host is <%s>, running version <%f>"},
	/**
	 * %s: date (14:18:55 Nov 28 2017)
	 */
	{RPL_CREATED, "This server was created <%s>"},
	{ERR_NONICKNAMEGIVEN, "No nickname given"},
	/**
	 * %s: nick
	 */
	{ERR_ERRONEUSNICKNAME, "<%s> :Erroneous nickname"},
	/**
	 * %s: nick
	 */
	{ERR_NICKNAMEINUSE, "<%s> :Nickname is already in use"},
	{0, NULL}
};

static const char *find_by_code(enum reply_code code)
{
	for (int i = 0; replies[i].message; ++i) {
		if (replies[i].code == code)
			return replies[i].message;
	}
	return NULL;
}

bool send_response(socket_t client, enum reply_code code, ...)
{
	const char *msg = find_by_code(code);
	char *format = NULL;
	va_list arguments;

	if (!msg || !allocate((void **)&format, strlen(msg) + 7, sizeof(char)))
		return false;
	sprintf(format, "%03d %s\r\n", code, msg);
	va_start(arguments, code);
	vdprintf(client, format, arguments);
	va_end(arguments);
	free(format);
	return true;
}