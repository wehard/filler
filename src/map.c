/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:39:22 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/05 23:21:18 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "ft_get_next_line.h"
#include "vector.h"
#include <stdlib.h>

t_map *create_map(int width, int height)
{
	t_map *map;

	map = (t_map*)malloc(sizeof(t_map));
	map->width = width;
	map->height = height;
	map->data = make_area(width, height);
	//debug_log("created map: %d %d\n", height, width);
	return (map);
}

void read_map_state(t_map *map)
{
	char *line;

	ft_get_next_line(STDIN, &line); // Skip first because it just has unnecessary stuff
	populate_area(map->data, map->width, map->height, 4);
	//print_area(map->data, map->width, map->height);
}

t_vec2i get_opponent_dir(t_map map)
{
	t_vec2i cur;
	t_vec2i pos;

	pos.x = 0;
	pos.y = 0;
	cur.y = 0;
	while (cur.y < map.height)
	{
		cur.x = 0;
		while (cur.x < map.width)
		{
			if (map.data[cur.y][cur.x] == 'x')
			{
				pos = cur;
				return (pos);
			}
			if (map.data[cur.y][cur.x] == 'X')
			{
				pos = cur;
			}
			cur.x++;
		}
		cur.y++;
	}
	return pos;
}

int	test_piece(t_map map, t_piece piece, t_vec2i pos)
{
	int num_overlap;
	t_vec2i m;
	t_vec2i p;

	num_overlap = 0;

	p.y = 0;
	m.y = pos.y;
	while (m.y < pos.y + piece.height)
	{
		p.x = 0;
		m.x = pos.x;
		while (m.x < pos.x + piece.width)
		{
			if (map.data[m.y][m.x] != '.' && piece.data[p.y][p.x] != '.')
				num_overlap++;
			p.x++;
			m.x++;
		}
		p.y++;
		m.y++;
	}
	return (num_overlap == 1);
}

t_vec2i get_decent_position(t_map map, t_piece piece)
{
	t_vec2i cur;

	cur.y = 0;
	while (cur.y < map.height)
	{
		cur.x = 0;
		while (cur.x < map.width)
		{
			if (test_piece(map, piece, cur))
			{
				t_vec2i c = calc_top_left_corner(piece);
				cur.x -= c.x;
				cur.y -= c.y;
				return (cur);
			}
			cur.x++;
		}
		cur.y++;
	}
	return (cur);
}


