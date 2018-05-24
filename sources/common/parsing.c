/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdlib.h>
#include <memory.h>

#include "client.h"

static unsigned int count_tabs(char *str)
{
	unsigned int tab = 0;

	for (int i = 0; str[i]; ++i) {
		if (str[i] == ' ')
			tab += 1;
	}
	return tab + 1;
}

#include <stdio.h>

static char *str_cut(char *str)
{
	char *find = strstr(str, "\r\n");

	if (find)
		*find = '\0';
	return str;
}

size_t strtab_len(char **strtab)
{
	int size = 0;

	for (; strtab[size]; ++size);
	return size;
}

char **str_to_strtab(char *str)
{
	int size = count_tabs(str);
	char **strtab = calloc(sizeof(char *), size + 1);
	char *tab = strtok(str, " ");

	if (!strtab)
		return NULL;
	for (int idx = 0; idx < size && tab; ++idx) {
		strtab[idx] = str_cut(tab);
		tab = strtok(NULL, " ");
	}
	return strtab;
}