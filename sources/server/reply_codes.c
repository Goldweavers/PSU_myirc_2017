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
#include "server.h"

const reply_t replies[] = {
	/**
	 * %s: nick
	 */
	{RPL_WELCOME, ":Welcome to the Internet Relay Network %s"},
	/**
	 * %s: servername
	 * %f: version
	 */
	{RPL_YOURHOST, ":Your host is %s, running version %04f"},
	/**
	 * %s: date (14:18:55 Nov 28 2017)
	 */
	{RPL_CREATED, ":This server was created %s"},
	{ERR_NONICKNAMEGIVEN, "NICK :No nickname given"},
	/**
	 * %s: nick
	 */
	{ERR_ERRONEUSNICKNAME, "%s :Erroneous nickname"},
	/**
	 * %s: nick
	 */
	{ERR_NICKNAMEINUSE, "%s :Nickname is already in use"},
	/**
	 * %s: command
	 * %s: reason
	 */
	{ERR_NEEDMOREPARAMS, "%s :%s"},
	/**
	 * %s: nick
	 * %s: channel
	 */
	{ERR_USERONCHANNEL, "%s %s :You are already on this channel"},
	/**
	 * %s: channel/nick
	 */
	{ERR_NOSUCHNICK, "%s :No such nick/channel"},
	/**
	 * %s: channel
	 * %s: reason
	 */
	{ERR_NOSUCHCHANNEL, "%s :%s"},

	{ERR_NOTEXTTOSEND, ":No text to send"},
	/**
	 * %s: channel
	 */
	{ERR_NOTONCHANNEL, "%s :You are not on this channel"},

	{RPL_LISTSTART, "Channel :Users Name"},
	/**
	 * %s: channel
	 * %d: number of users in
	 */
	{RPL_LIST, "%s %d :Topic not implemented yet"},

	{RPL_LISTEND, ":End of channel list."},
	/**
	 * %d: number of channel
	 */
	{RPL_LUSERCHANNELS, "%d :channels formed"},
	/**
	 * %d: number of clients
	 */
	{RPL_LUSERME, ":I have %d clients and 1 servers"},
	/**
	 * %s: channel
	 * %s: users nicknames space separated
	 */
	{RPL_NAMREPLY, "= %s :%s"},
	/**
	 * %s: channel
	 */
	{RPL_ENDOFNAMES, "%s :End of /NAMES list."},

	{RPL_USERSSTART, ":UserID Terminal Host"},

	{RPL_USERS, "%-8s %-9s %-8s"},

	{RPL_ENDOFUSERS, ":End of users"},
	/**
	 * %s: command name
	 */
	{ERR_NOTREGISTERED, "%s :You have not registered"},

	{RPL_NOUSERS, ":Nobody logged in"},
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

static bool get_format(char **pFormat, ...)
{
	char *format = ":%s %03d %s %s\r\n";
	va_list original;
	va_list copy;

	va_start(original, pFormat);
	va_copy(copy, original);
	size_t needed = (size_t)vsnprintf(NULL, 0, format, original);
	va_end(original);
	if (allocate((void **)pFormat, needed + 1, sizeof(char)) == false)
		return false;
	vsprintf(*pFormat, format, copy);
	va_end(copy);
	return true;
}

bool send_response(socket_t client, enum reply_code code, ...)
{
	const char *msg = find_by_code(code);
	user_t *user = find_user_by_socket(server.users, client);
	char *format = NULL;
	va_list original;

	if (!msg || !get_format(&format, SERVERNAME, code, user->nickname, msg))
		return false;
	va_start(original, code);
	vdprintf(client, format, original);
	va_end(original);
	free(format);
	return true;
}