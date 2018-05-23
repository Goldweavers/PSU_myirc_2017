/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/
#ifndef PSU_MYIRC_2017_CLIENT_H
#define PSU_MYIRC_2017_CLIENT_H

#include "common.h"

/* Commands */

int msg(char *parameters[]);

int server(char *parameters[]);

/* !Commands */

bool find_client_commands(char *name, command_ptr *function);

#endif //PSU_MYIRC_2017_CLIENT_H
