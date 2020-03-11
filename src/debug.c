/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:58:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/11 14:55:26 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <stdio.h>
#include "debug.h"

void debug_log_fput(const char *str)
{
	FILE	*file;

	file = fopen("debug.log", "a");
	fputs(str, file);
	fputc('\n', file);
	fclose(file);
}

FILE	*g_file;

void init_logger(char *filename, char *mode)
{
	g_file = fopen(filename, mode);
	debug_log("\033[0;36m### init logger ###\033[0m\n");
}

void close_logger(void)
{
	debug_log("\033[0;33m### closing logger ###\033[0m\n");
	fclose(g_file);
}

void debug_log(const char *format,...)
{
	va_list valist;
	//FILE	*file;

	va_start(valist, format);
	//file = fopen("debug.log", "a");
	vfprintf(g_file, format, valist);
	//fputc('\n', g_file);
	//fclose(file);
}

void debug_log_char(const char c)
{
	fputc(c, g_file);
}

void print_area(char **area, int width, int height)
{
	int r;
	int c;

	debug_log("    01234567890123456789\n");
	r = 0;
	while (r < height)
	{
		debug_log("%3d ", r);
		c = 0;
		while (c < width)
		{
			debug_log_char(area[r][c]);
			c++;
		}
		debug_log_char('\n');
		r++;
	}
}

void print_heat_map(int *map, int width, int height)
{
	int r;
	int c;

	r = 0;
	while (r < height)
	{
		c = 0;
		while (c < width)
		{
			debug_log("%3d", map[r * width + c]);
			c++;
		}
		debug_log_char('\n');
		r++;
	}
	debug_log_char('\n');
}
