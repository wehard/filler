/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:58:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/26 19:41:54 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "debug.h"

void	init_logger(char *filename, char *mode)
{
	g_file = fopen(filename, mode);
	debug_log("\033[0;36m### init logger ###\033[0m\n");
}

void	close_logger(void)
{
	debug_log("\033[0;33m### closing logger ###\033[0m\n");
	fclose(g_file);
}

void	debug_log(const char *format, ...)
{
	va_list valist;

	va_start(valist, format);
	vdprintf(2, format, valist);
	va_end(valist);
}

void	print_area(char **area, int width, int height)
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
			debug_log("%c", area[r][c]);
			c++;
		}
		debug_log("\n");
		r++;
	}
}

void	print_heat_map(int *map, int width, int height)
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
		debug_log("\n");
		r++;
	}
	debug_log("\n");
}
