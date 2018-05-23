/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Copyright (c) 2018 by Julien Sarriot
** All rights reserved.
*/

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <memory.h>
#include <time.h>

#include "common.h"

const char *geterr(void)
{
	return strerror(errno);
}

int eprintf(int exit_code, const char *format, ...)
{
	time_t rawtime = time(NULL);
	struct tm *info = localtime(&rawtime);
	va_list args;

	va_start(args, format);
	dprintf(STDERR_FILENO, "%d:%d -!- MyIRC: ", info->tm_hour, info->tm_min);
	vdprintf(STDERR_FILENO, format, args);
	va_end(args);
	return exit_code;
}