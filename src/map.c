/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:39:22 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/12 15:21:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "ft_get_next_line.h"
#include "vector.h"
#include <stdlib.h>
#include "debug.h"
#include "math.h"

t_map *create_map(char *line)
{
	t_map	*map;
	char	**split;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		ft_panic("create_map: malloc failed!");
	split = ft_strsplit(line, ' ');
	map->width = ft_atoi(split[2]);
	map->height = ft_atoi(split[1]);
	map->data = make_area(map->width, map->height);
	debug_log("map size: r%d c%d\n", map->height, map->width);
	return (map);
}

void read_map_state(t_map *map)
{
	char *line;

	ft_get_next_line(STDIN, &line); // Skip first because it just has unnecessary stuff
	populate_area(map->data, map->width, map->height, 4);
}
