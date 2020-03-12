/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:35:45 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/12 14:12:06 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "ft_get_next_line.h"
#include "debug.h"
#include <stdlib.h>

char	**make_area(int width, int height)
{
	char	**area;
	int		y;

	area = (char**)malloc(sizeof(char*) * height);
	y = 0;
	while (y < height)
	{
		area[y] = (char*)malloc(sizeof(char) * width);
		ft_bzero(area[y], width);
		y++;
	}
	return (area);
}

void	populate_area(char **area, int width, int height, int line_offset)
{
	char	*line;
	int		row;

	row = 0;
	while (row < height && ft_get_next_line(STDIN, &line))
	{
		if (line == NULL)
			continue;
		area[row] = ft_strncpy(area[row], line + line_offset, width);
		free(line);
		row++;
	}
}
