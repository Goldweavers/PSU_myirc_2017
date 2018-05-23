/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <errno.h>
#include <memory.h>

#include "common.h"

static bool str_to_uint16(char *string, uint16_t *pInt)
{
	char *end = NULL;
	intmax_t val = strtoimax(string, &end, 10);

	errno = 0;
	if (end && strlen(end) > 0)
		return false;
	if (errno == ERANGE || val < 0 || val > UINT16_MAX)
		return false;
	*pInt = (uint16_t) val;
	return true;
}

bool str_to_port(char *string, in_port_t *pPort)
{
	if (!string || str_to_uint16(string, pPort) == false)
		return false;
	return *pPort > 0;
}