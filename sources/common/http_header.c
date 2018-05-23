/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
**
*/

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <server.h>
#include <unistd.h>
#include "common.h"

char *generate_header(char *info)
{
	char *header = calloc(1, HTTP_HEADER_LENGTH(info));
	int content_length = strlen(format_content(info));

	sprintf(header, HTTP_FORMAT, HTTP_HEADER_CODE, \
HTTP_HEADER_CONTENT_TYPE, HTTP_HEADER_CONTENT_LENGTH, content_length, \
format_content(info));
	return header;
}

char *format_content(char *info)
{
	strtok(info, "\r\n");
	return info;
}

char *update_header(char *header, char *field_name, char *info)
{
	size_t header_size = strlen(header);
	char backup[strlen(header)];
	char update[strlen(info) + strlen(field_name) + CRLF_SIZE + 1];
	char *new;
	int remove_size = 0;

	if (strcmp(field_name, HTTP_HEADER_CONTENT) == 0)
		return update_header_content(header, info, new);
	strcpy(backup, strstr(header, field_name));
	if (backup == NULL)
		return NULL;
	for (; backup[remove_size] != '\n'; remove_size++);
	memset(header + (strlen(header) - strlen(backup)), 0, strlen(backup));
	sprintf(update, "%s%s\r\n", field_name, info);
	new = calloc(header_size + strlen(update), sizeof(char));
	strcat(strcat(new, header), update);
	strcat(new, backup + remove_size + 1);
	free(header);
	return new;
}

char *update_header_content(char *header, char *info, char *new)
{
	int endline = 0;
	size_t header_size = strlen(header);

	for (int i = 0; i < strlen(header); i++) {
		if (header[i] == '\n')
			endline = i;
	}
	memset(header + endline + 1, 0, strlen(header) - endline);
	new = calloc(header_size + strlen(info), sizeof(char));
	strcat(strcat(new, header), info);
	return update_header(new, HTTP_HEADER_CONTENT_LENGTH, \
size_t_to_char_array(strlen(info)));
}

char *size_t_to_char_array(int size)
{
	char *result = calloc(1, sizeof(size_t));

	sprintf(result, "%d", size);
	return result;
}
