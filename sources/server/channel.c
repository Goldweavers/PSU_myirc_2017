/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stddef.h>
#include <memory.h>

#include "server.h"

channel_t *find_channel_by_name(channel_t *channels, const char *name)
{
	for (node_t *node = channels; node != NULL; node = node->next) {
		if (strcmp(((channel_t *)node->data)->name, name) == 0)
			return (channel_t *)node->data;
	}
	return NULL;
}