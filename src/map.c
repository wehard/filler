/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:39:22 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/07 17:35:19 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "ft_get_next_line.h"
#include "vector.h"
#include <stdlib.h>
#include "debug.h"
#include "math.h"

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

int	test_piece(t_filler *filler, t_piece piece, t_vec2i pos)
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
			if (piece.data[p.y][p.x] == ASTERISK && filler->map->data[m.y][m.x] == filler->opp)
				return (0);
			if (filler->map->data[m.y][m.x] != '.' && piece.data[p.y][p.x] != '.')
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

t_vec2 get_player_start(char player, t_filler *filler)
{
	t_vec2i cur;

	if (player == filler->player && filler->player_start_set)
		return (filler->player_start);
	if (player == filler->opp && filler->opp_start_set)
		return (filler->opp_start);
	cur.x = 0;
	cur.y = 0;
	while (cur.y < filler->map->height)
	{
		cur.x = 0;
		while (cur.x < filler->map->width)
		{
			if (filler->map->data[cur.y][cur.x] == player)
			{
				debug_log("player %c start: r%d c%d\n", player, cur.y, cur.x);
				if (player == filler->player)
				{
					filler->player_start_set = 1;
					filler->player_start = ft_make_vec2(cur.x, cur.y);
					return (filler->player_start);
				}
				else if (player == filler->opp)
				{
					filler->opp_start_set = 1;
					filler->opp_start = ft_make_vec2(cur.x, cur.y);
					return (filler->opp_start);
				}
			}
			cur.x++;
		}
		cur.y++;
	}
	return (ft_make_vec2(cur.x, cur.y));
}

t_vec2i get_pos_fallback(t_filler *filler, t_piece piece)
{
	t_vec2i cur;
	t_map map;

	map = *filler->map;
	cur.y = 0;
	while (cur.y < map.height - piece.height + piece.max_offset.y + 1)
	{
		cur.x = 0;
		while (cur.x < map.width - piece.width + piece.max_offset.x + 1)
		{
			if (test_piece(filler, piece, cur))
			{
				debug_log("found pos\n");
				//cur.x -= piece.min_offset.x;
				//cur.y -= piece.min_offset.y;
				return (cur);
			}
			cur.x++;
		}
		cur.y++;
	}
	return (cur);
}

t_vec2i get_position(t_filler *filler, t_piece piece)
{
	int	found_pos;
	t_vec2i cur;

	found_pos = 0;
	t_vec2 opp_pos = get_player_start(filler->opp, filler);

	if (filler->player_start.x == -1 && filler->player_start.y == - 1)
		filler->player_start = get_player_start(filler->player, filler);
	cur.y = filler->player_start.y;
	while (cur.y < opp_pos.y - piece.height + piece.max_offset.y + 1)
	{
		cur.x = filler->player_start.x;
		while (cur.x < opp_pos.x - piece.width + piece.max_offset.x + 1)
		{
			if (test_piece(filler, piece, cur))
			{
				debug_log("found pos\n");
				//cur.x -= piece.min_offset.x;
				//cur.y -= piece.min_offset.y;
				return (cur);
			}
			cur.x++;
		}
		cur.y++;
	}
	if (!found_pos)
		cur = get_pos_fallback(filler, piece);
	return (cur);
}

int	search_radius(t_filler *filler, t_piece piece, t_vec2 start_pos, int radius, t_vec2 *valid_pos)
{
	int spread;
	int leg_count;
	t_vec2i cur;
	t_vec2 opp_pos;
	int r;

	if (start_pos.x < 0 || start_pos.x > filler->map->width)
		return (0);
	if (start_pos.y < 0 || start_pos.y > filler->map->height)
		return (0);

	opp_pos = get_player_start(filler->opp, filler);

	t_vec2 direction = ft_normalize_vec2(ft_sub_vec2(opp_pos, start_pos));
	//debug_log("dir %.2f %.2f\n", direction.x, direction.y);

	spread = 45;
	leg_count = 2;
	r = 1;
	filler->spider_angle = spread - ft_rad_to_deg(tan(direction.y / direction.x)) / leg_count;
	//debug_log("angle %d\n", filler->spider_angle);
	if (filler->spider_angle >= spread)
		filler->spider_angle = ft_rad_to_deg(tan(direction.y / direction.x)) - spread / leg_count;

	while (r < radius)
	{
		while (filler->spider_angle < spread)
		{
			cur.x = start_pos.x + cos(ft_deg_to_rad(filler->spider_angle)) * radius;
			cur.y = start_pos.y + sin(ft_deg_to_rad(filler->spider_angle)) * radius;
			if (cur.x > 0 && cur.x < filler->map->width - piece.width - piece.max_offset.x + 1 &&
				cur.y > 0 && cur.y < filler->map->height - piece.height - piece.max_offset.y + 1)
			{
				if (test_piece(filler, piece, cur))
				{
					*valid_pos = ft_make_vec2(cur.x, cur.y);
					return (1);
				}
				else
					return (search_radius(filler, piece, ft_make_vec2(cur.x, cur.y), 20, valid_pos));
			}
			filler->spider_angle += spread;
		}
		r++;
	}
	return (0);
}

t_vec2i spider_strategy(t_filler *filler, t_piece piece)
{
	int radius;
	t_vec2 start_pos;
	t_vec2 valid_pos;

	start_pos = get_player_start(filler->player, filler);
	valid_pos = ft_make_vec2(0,0);
	radius = 20;
	if (search_radius(filler, piece, start_pos, radius, &valid_pos))
		return (ft_make_vec2i(valid_pos.x, valid_pos.y));
	debug_log("fallback\n");
	return (get_pos_fallback(filler, piece));
}
