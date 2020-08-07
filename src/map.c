/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:39:22 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/07 15:12:06 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "ft_get_next_line.h"
#include "vector.h"
#include <stdlib.h>
#include "debug.h"
#include "math.h"

t_map	*create_map(char *line)
{
	t_map	*map;
	char	**split;
	int		i;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		ft_panic("create_map: malloc failed!");
	split = ft_strsplit(line, ' ');
	map->width = ft_atoi(split[2]);
	map->height = ft_atoi(split[1]);
	map->data = make_area(map->width, map->height);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (map);
}

void	init_map(t_filler *filler, char *line)
{
	filler->map = create_map(line);
	filler->heat_map = create_heat_map(filler->map->width, filler->map->height);
}

void	read_map_state(t_map *map)
{
	char *line;

	ft_get_next_line(STDIN, &line);
	populate_area(map->data, map->width, map->height, 4);
	free(line);
}
