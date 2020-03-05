/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:58:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/05 22:13:00 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <stdio.h>

void debug_log(const char *str)
{
	FILE	*file;

	file = fopen("debug.log", "a");
	fputs(str, file);
	fputc('\n', file);
	fclose(file);
}


void debug_log2(const char *format,...)
{
	va_list valist;
	FILE	*file;

	va_start(valist, format);
	file = fopen("debug.log", "a");
	vfprintf(file, format, valist);
	fclose(file);
}


void print_area(char **area, int width, int height)
{
	int r;
	int c;

	r = 0;
	while (r < height)
	{
		c = 0;
		while (c < width)
		{
			debug_log(&area[r][c]);
			c++;
		}
		debug_log("\n");
		r++;
	}
}
