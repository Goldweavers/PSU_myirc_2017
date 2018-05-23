/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/
#ifndef PSU_MYIRC_2017_COMMON_H
#define PSU_MYIRC_2017_COMMON_H

#include <netinet/in.h>
#include <stdbool.h>

/**
 * Custom Epitech exiting error code
 */
#ifndef EPITECH_ERROR
	#define EPITECH_ERROR 84
#endif

#define HTTP_FORMAT ("%s%s%s%d\r\n%s")
#define HTTP_HEADER_CODE ("HTTP/1.1 200 OK\r\n")
#define HTTP_HEADER_CONTENT_TYPE ("content-type: text/plain\r\n")
#define HTTP_HEADER_CONTENT_LENGTH ("content-length: ")
#define HTTP_HEADER_CONTENT ("content")
#define HTTP_HEADER_LENGTH(info) (67 + sizeof(size_t) + strlen(info))

#define CRLF_SIZE (2)

typedef struct node {
	struct node *next;
	void *data;
} node_t;


/* generic_list.c */
bool push_front(struct node **head, void *new_data, size_t datasize);

bool push_back(struct node **head, void *new_data, size_t datasize);

bool delete_node(struct node **origin, struct node *todel);
/* !generic_list.c */

/* http_header.c */
char *format_content(char *info);

char *update_header(char *header, char *field_name, char *info);

char *generate_header(char *info);

char *size_t_to_char_array(int size);

char *update_header_content(char *header, char *info, char *new);
/* !http_header.c */


/* error.c */
const char *geterr(void);

int eprintf(int exit_code, const char *format, ...);
/* !error.c */

/* conversion.c */
bool str_to_port(char *string, in_port_t *pPort);
/* !conversion.c */

/* memory.c */
void freeset(void **ptr);

bool allocate(void **ptr, size_t nmemb, size_t size);
/* !memory.c */

/* socket.c */
typedef int socket_t;

socket_t socket_init(const char *name);

struct sockaddr_in *init_interface(in_addr_t address, in_port_t port);

int socket_bind(socket_t sock, \
in_addr_t address, in_port_t port, int connections);

int socket_connect(socket_t sock, in_addr_t address, in_port_t port);
/* !socket.c */


#endif //PSU_MYIRC_2017_COMMON_H
