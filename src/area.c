/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:35:45 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/06 17:26:06 by wkorande         ###   ########.fr       */
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

	if (!(area = (char**)malloc(sizeof(char*) * height)))
		ft_panic("make_aread: malloc failed!");
	y = 0;
	while (y < height)
	{
		if (!(area[y] = (char*)malloc(sizeof(char) * width)))
			ft_panic("make_aread: malloc failed!");
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

void	destroy_area(char **area, int rows)
{
	int row;

	row = 0;
	while (row < rows)
		free(area[row++]);
	free(area);
}
