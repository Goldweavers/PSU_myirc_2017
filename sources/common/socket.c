/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "common.h"

/**
 * Create a new socket
 * @param {string} name - Protocol name
 * @return {number} - newly created socket
 */
bool socket_init(const char *name, socket_t *sock)
{
	int opts = SO_REUSEADDR | SO_REUSEPORT;
	struct protoent *protocol = getprotobyname(name);
	int enabled = 1;

	if (protocol == NULL)
		return eprintf(false, "Invalid protocol: %s\n", name);
	*sock = socket(AF_INET, SOCK_STREAM, protocol->p_proto);
	if (*sock == -EXIT_FAILURE)
		return eprintf(false, "socket creation: %s\n", geterr());
	setsockopt(*sock, SOL_SOCKET, opts, &enabled, sizeof(enabled));
	return true;
}

/**
 * Create new interface of IP protocol family
 * @param {number} address
 * @param {number} port
 * @return
 */
struct sockaddr_in *init_interface(in_addr_t address, in_port_t port)
{
	struct sockaddr_in *sin = calloc(1, sizeof(struct sockaddr_in));

	if (sin != NULL) {
		sin->sin_port = htons(port);
		sin->sin_addr.s_addr = htonl(address);
		sin->sin_family = AF_INET;
	}
	return sin;
}

/**
 * Start listening for incoming connection
 * @param {number} sock
 * @param {number} connections - Maximum incoming connections in queue
 * @return
 */
static int socket_listen(socket_t sock, int connections)
{
	int status = listen(sock, connections);

	if (status == -EXIT_FAILURE)
		return eprintf(-1, "listen: %s\n", geterr());
	return EXIT_SUCCESS;
}

/**
 *
 * @param {number} sock - Socket to bind
 * @param {number} address
 * @param {number} port
 * @param {number} connections - Maximum incoming connections in queue
 * @return
 */
int socket_bind(socket_t sock, \
in_addr_t address, in_port_t port, int connections)
{
	struct sockaddr_in *sin = init_interface(address, port);
	int code = 0;

	if (sin == NULL)
		return eprintf(-1, "interface: %s\n", geterr());
	code = bind(sock, (const struct sockaddr *)sin, sizeof(*sin));
	free(sin);
	if (code == -EXIT_FAILURE)
		return eprintf(-1, "bind: %s\n", geterr());
	return socket_listen(sock, connections);
}

/**
 * Connect to the specified {address} and {port}
 * @param {number} sock
 * @param {number} address
 * @param {number} port
 * @return
 */
int socket_connect(socket_t sock, in_addr_t address, in_port_t port)
{
	struct sockaddr_in *sin = init_interface(address, port);
	int status = 0;

	if (sin == NULL)
		return eprintf(-1, "interface: %s\n", geterr());
	status = connect(sock, (const struct sockaddr *)sin, sizeof(*sin));
	free(sin);
	if (status == -EXIT_FAILURE)
		return eprintf(-1, "connect: %s\n", geterr());
	return EXIT_SUCCESS;
}

/**
 * Wait & Accept incoming connection
 * @param {number} listenfd
 * @param client
 * @return
 */
bool socket_accept(int listenfd, client_t *client)
{
	struct sockaddr_in remote;
	socklen_t addrlen = sizeof(remote);

	client->socket = accept(listenfd, (struct sockaddr *)&remote, &addrlen);
	if (client->socket == -EXIT_FAILURE)
		return false;
	inet_ntop(AF_INET, &(remote.sin_addr), client->ip, INET_ADDRSTRLEN);
	return true;
}