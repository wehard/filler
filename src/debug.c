/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:58:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/05 19:25:38 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>

void debug_log(const char *str)
{
	FILE	*file;

	file = fopen("debug.log", "a");
	fputs(str, file);
	fputc('\n', file);
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
