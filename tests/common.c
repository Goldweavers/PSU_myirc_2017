/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** test for common functions
*/


#include <criterion/criterion.h>
#include <stdio.h>
#include "unistd.h"
#include "common.h"

Test(str_to_port, valid_port)
{
	in_port_t port;

	cr_assert_eq(str_to_port("1234", &port), true);
	cr_assert_eq(port, 1234);
}

Test(str_to_port, negative_port)
{
	in_port_t port;

	cr_assert_eq(str_to_port("-42", &port), false);
}

Test(str_to_port, out_of_range_port)
{
	in_port_t port;

	cr_assert_eq(str_to_port("70000", &port), false);
}

int sock = -EXIT_FAILURE;

Test(socket_bind, valid_bind)
{
	sock = socket_init("TCP");
	int code = socket_bind(sock, INADDR_ANY, 1234, 5);

	cr_assert_eq(code, sock == -1 ? -1 : 0);
	cr_assert_eq(socket_bind(sock, INADDR_ANY, 1234, 5), -1);
}

Test(socket_bind, inval_bind)
{
	cr_assert_eq(socket_bind(sock, INADDR_ANY, 1234, 5), -1);
}

Test(socket_connect, invalid_connect)
{
	cr_assert_eq(socket_connect(sock, INADDR_ANY, 1234), -1);
}

Test(socket_connect, valid_connect)
{
	struct sockaddr_in in;
	int len = sizeof(in);
	int csock = accept(sock, (struct sockaddr *)&in, &len);

	if (csock != -EXIT_FAILURE)
		cr_assert_eq(socket_connect(sock, INADDR_ANY, 1234), 0, "%d");
	else
		cr_assert_eq(socket_connect(sock, INADDR_ANY, 1234), -1, "%d");
	close(sock);
}

Test(push_front, valid_front_push_with_int)
{
	struct node *node = NULL;
	bool is_valid;

	int arr[] = {1, 2, 3, 4, 5}, i;

	for (i = 0; i < 5; i++) {
		is_valid = push_front(&node, &arr[i], sizeof(int));
		cr_assert_eq(is_valid, true, "%d");
	}
	i = 4;
	while (node != NULL) {
		cr_assert_eq(*(int *)node->data, arr[i], "%d");
		node = node->next;
		i -= 1;
	}
}

typedef struct test {
	float nb;
} test;

Test(push_front, valid_front_push_with_different_types)
{
	struct node *node = NULL;
	bool is_valid;

	int first = 77;
	char second[] = "frontpush";
	bool third = false;
	struct test *forth = calloc(1, sizeof(struct test));
	forth->nb = 17.7;

	is_valid = push_front(&node, &first, sizeof(int));
	cr_assert_eq(is_valid, true);

	is_valid = push_front(&node, second, strlen(second));
	cr_assert_eq(is_valid, true);

	is_valid = push_front(&node, &third, sizeof(bool));
	cr_assert_eq(is_valid, true);

	is_valid = push_front(&node, forth, sizeof(*forth));
	cr_assert_eq(is_valid, true);

	struct test *result = node->data;
	cr_assert_eq(result->nb, forth->nb);
	node = node->next;

	cr_assert_eq(*(bool *)node->data, third);
	node = node->next;

	cr_assert_str_eq(node->data, second);
	node = node->next;

	cr_assert_eq(*(int *)node->data, first);
}

Test(push_back, valid_back_push_with_int)
{
	struct node *node = NULL;
	bool is_valid;

	int arr[] = {1, 2, 3, 4, 5}, i;

	unsigned size = sizeof(int);
	for (i = 0; i < 5; i++) {
		is_valid = push_back(&node, &arr[i], size);
		cr_assert_eq(is_valid, true);
	}
	i = 0;
	while (node != NULL) {
		cr_assert_eq(*(int *)node->data, arr[i]);
		node = node->next;
		i += 1;
	}
}

Test(push_back, valid_push_back_with_different_types)
{
	struct node *node = NULL;
	bool is_valid;

	int first = 77;
	char second[] = "pushback";
	bool third = false;
	struct test *forth = calloc(1, sizeof(struct test));
	forth->nb = 17.7;

	is_valid = push_back(&node, &first, sizeof(int));
	cr_assert_eq(is_valid, true);

	is_valid = push_back(&node, second, strlen(second) + 1);
	cr_assert_eq(is_valid, true);

	is_valid = push_back(&node, &third, sizeof(bool));
	cr_assert_eq(is_valid, true);

	is_valid = push_back(&node, forth, sizeof(*forth));
	cr_assert_eq(is_valid, true);

	cr_assert_eq(*(int *)node->data, first);
	node = node->next;

	cr_assert_str_eq(node->data, second);
	node = node->next;

	cr_assert_eq(*(bool *)node->data, third);
	node = node->next;

	struct test *result = node->data;
	cr_assert_eq(result->nb, forth->nb);
}


Test(delete_node, valid_push_and_node_deletion)
{
	struct node *node = NULL;
	struct node *todel = NULL;
	int values[] = {1, 2, 3, 4}, i = -1;
	bool is_valid = false;

	for (i; i < 4; i++) {
		is_valid = push_back(&node, &values[i], sizeof(int));
		if (i == 1)
			todel = node;
		cr_assert_eq(is_valid, true);
	}

	i = 0;
	delete_node(&node, todel);
	for(;node != NULL;node = node->next) {
		if (i == 1)
			cr_assert_eq(*(int*)node->data, 2);
		i += 1;
	}
}

Test(header_generation, valid_http_header_generatiion)
{
	char *header;
	char *expected_header;
	char *info = calloc(7, sizeof(char));

	strcpy(info, "TEST\r\n");
	expected_header = calloc(HTTP_HEADER_LENGTH(info), sizeof(char));
	expected_header = "HTTP/1.1 200 OK\r\ncontent-type: text/plain\r\n" \
		   "content-length: 4\r\nTEST";
	header = generate_header(info);
	cr_assert_str_eq(header, expected_header);
}
