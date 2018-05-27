/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
**
*/


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct cbuf{
	uint8_t *buffer;
	size_t end;
	size_t start;
	size_t size;
} cbuf_t;

bool fill_cbuf(cbuf_t * cbuf, uint8_t data);
bool get_cbuf(cbuf_t * cbuf, uint8_t * data);
bool is_cbuf_empty(cbuf_t cbuf);
bool is_cbuf_full(cbuf_t cbuf);


bool is_cbuf_empty(cbuf_t cbuf)
{
	return (cbuf.end == cbuf.start);
}

bool is_cbuf_full(cbuf_t cbuf)
{
	return ((cbuf.end + 1) % cbuf.size) == cbuf.start;
}

bool fill_cbuf(cbuf_t * cbuf, uint8_t data)
{

	if (cbuf != NULL) {
		cbuf->buffer[cbuf->end] = data;
		cbuf->end = (cbuf->end + 1) % cbuf->size;

		if(is_cbuf_empty(*cbuf) == true)
			cbuf->start = (cbuf->start + 1) % cbuf->size;

		return true;
	}

	return false;
}

bool get_cbuf(cbuf_t * cbuf, uint8_t * data)
{
	if (cbuf != NULL && data != NULL) {
		if (is_cbuf_empty(*cbuf) == false) {
			*data = cbuf->buffer[cbuf->start];
			cbuf->start = (cbuf->start + 1) % cbuf->size;
			return true;
		}
	}
	return false;
}

bool create_cbuf(cbuf_t **cbuf, size_t size)
{
	long page_size = sysconf(_SC_PAGESIZE);

	size = ((size % page_size != 0) + size / page_size) * page_size;

	(*cbuf) = calloc(sizeof(**cbuf) + (size * sizeof(uint8_t)), \
sizeof(void));
	(*cbuf)->buffer = (void *)*cbuf + sizeof(**cbuf);
	(*cbuf)->size = size;
}
