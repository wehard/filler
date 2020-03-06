/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:39:22 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/06 19:51:03 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "ft_get_next_line.h"
#include "vector.h"
#include <stdlib.h>
#include "debug.h"

t_map *create_map(int width, int height)
{
	t_map *map;

	map = (t_map*)malloc(sizeof(t_map));
	map->width = width;
	map->height = height;
	map->data = make_area(width, height);
	debug_log("map size: r%d c%d\n", height, width);
	return (map);
}

void read_map_state(t_map *map)
{
	char *line;

	ft_get_next_line(STDIN, &line); // Skip first because it just has unnecessary stuff
	populate_area(map->data, map->width, map->height, 4);
	//print_area(map->data, map->width, map->height);
}

t_vec2i get_opponent_pos(t_map map)
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
			if (map.data[cur.y][cur.x] == 'X')
			{
				pos = cur;
				return (pos);
			}
			cur.x++;
		}
		cur.y++;
	}
	return pos;
}

int	test_piece(t_filler filler, t_map map, t_piece piece, t_vec2i pos)
{
	int num_overlap;
	t_vec2i m;
	t_vec2i p;

	num_overlap = 0;
	p.y = piece.min_offset.y;
	m.y = pos.y;
	while (m.y < pos.y + piece.height - piece.max_offset.y && p.y < piece.height - piece.max_offset.y)
	{
		p.x = piece.min_offset.x;
		m.x = pos.x;
		while (m.x < pos.x + piece.width - piece.max_offset.x && p.x < piece.width - piece.max_offset.x)
		{
			if (piece.data[p.y][p.x] == ASTERISK && map.data[m.y][m.x] == filler.opp)
				return (0);
			if (map.data[m.y][m.x] != '.' && piece.data[p.y][p.x] != '.')
				num_overlap++;
			p.x++;
			m.x++;
		}
		p.y++;
		m.y++;
	}
	//debug_log("num overlap: %d\n", num_overlap);
	return (num_overlap == 1);
}

t_vec2i get_player_start(t_filler *filler, t_map map)
{
	t_vec2i cur;


	cur.x = 0;
	cur.y = 0;
	while (cur.y < map.height)
	{
		cur.x = 0;
		while (cur.x < map.width)
		{
			if (map.data[cur.y][cur.x] == filler->player)
			{
				debug_log("player start: r%d c%d\n", cur.y, cur.x);
				return (cur);
			}
			cur.x++;
		}
		cur.y++;
	}
	return (cur);
}

t_vec2i get_decent_position(t_filler filler, t_map map, t_piece piece)
{
	t_vec2i cur;

	cur.y = 0;
	while (cur.y < map.height - piece.height + piece.max_offset.y + 1)
	{
		cur.x = 0;
		while (cur.x < map.width - piece.width + piece.max_offset.x + 1)
		{
			if (test_piece(filler, map, piece, cur))
			{
				debug_log("found pos\n");
				cur.x -= piece.min_offset.x;
				cur.y -= piece.min_offset.y;
				return (cur);
			}
			cur.x++;
		}
		cur.y++;
	}
	return (cur);
}

t_vec2i get_position(t_filler *filler, t_map map, t_piece piece)
{
	t_vec2i cur;
	int search_size;

	search_size = 10;

	t_vec2i opp_pos = get_opponent_pos(map);

	if (filler->player_start.x == -1 && filler->player_start.y == - 1)
		filler->player_start = get_player_start(filler, map);
	cur.y = filler->player_start.y;
	if (cur.y < 0)
		cur.y = 0;
	while (cur.y < opp_pos.y - piece.height + piece.max_offset.y + 1)
	{
		cur.x = filler->player_start.x;
		if (cur.x < 0)
			cur.x = 0;
		while (cur.x < opp_pos.x - piece.width + piece.max_offset.x + 1)
		{
			if (test_piece(*filler, map, piece, cur))
			{
				debug_log("found pos\n");
				cur.x -= piece.min_offset.x;
				cur.y -= piece.min_offset.y;
				return (cur);
			}
			cur.x++;
		}
		cur.y++;
	}
	return (cur);
}

