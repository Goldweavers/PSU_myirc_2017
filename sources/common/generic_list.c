/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
**
*/


#include <printf.h>
#include <string.h>
#include "common.h"
#include "stdlib.h"

bool push_front(struct node **head, void *new_data, size_t datasize)
{
	struct node *new = calloc(1, sizeof(struct node) + datasize);

	if (new == NULL)
		return false;
	new->next = (*head);
	if (datasize) {
		new->data = (void *)new + sizeof(*new);
		memcpy(new->data, new_data, datasize);
	} else
		new->data = new_data;
	(*head) = new;
	return true;
}

bool push_back(struct node **head, void *new_data, size_t datasize)
{
	struct node *new = calloc(1, sizeof(struct node) + datasize);
	struct node *last = *head;

	if (new == NULL)
		return false;
	new->data = (void *)(new) + sizeof(*new);
	memcpy(new->data, new_data, datasize);
	if (*head != NULL) {
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	} else
		(*head) = new;
	return true;
}

#include <stdio.h>

bool delete_node(struct node **origin, void *todel)
{
	struct node *next;

	if ((*origin) == NULL)
		return false;
	else if ((*origin)->data == todel) {
		next = (*origin)->next;
		free(*origin);
		*origin = next;
		return true;
	} else {
		delete_node(&((*origin)->next), todel);
		return true;
	}
}
