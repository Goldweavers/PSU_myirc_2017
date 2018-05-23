/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdlib.h>

#include "common.h"

void freeset(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

bool allocate(void **ptr, size_t nmemb, size_t size)
{
	*ptr = calloc(nmemb, size);

	return *ptr != NULL;
}