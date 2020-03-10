/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:39:22 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/10 12:46:53 by wkorande         ###   ########.fr       */
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
	//debug_log("map size: r%d c%d\n", height, width);
	return (map);
}

void read_map_state(t_map *map)
{
	char *line;

	ft_get_next_line(STDIN, &line); // Skip first because it just has unnecessary stuff
	populate_area(map->data, map->width, map->height, 4);
	//print_area(map->data, map->width, map->height);
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

int search_area(t_filler *filler, t_piece piece, t_vec2 pos, int size, t_vec2 *valid_pos)
{
	t_vec2i cur;
	int half_size;

	half_size = size / 2;
	cur.y = pos.y - half_size;
	if (cur.y < 0)
		cur.y = 0;
	while (cur.y < pos.y + half_size && cur.y < filler->map->height - piece.width - piece.max_offset.y + 1)
	{
		cur.x = pos.x - half_size;
		if (cur.x < 0)
			cur.x = 0;
		while (cur.x < pos.x + half_size && cur.x < filler->map->width - piece.width + piece.max_offset.x + 1)
		{
			if (test_piece(filler, piece, cur))
			{
				*valid_pos = ft_make_vec2(cur.x, cur.y);
					return (1);
			}
			cur.x++;
		}
		cur.y++;
	}
	return (0);
}


int	search_radius(t_filler *filler, t_piece piece, t_search_info info, t_vec2 *valid_pos)
{
	t_vec2i cur;
	int angle;

	while (info.beg_rad < info.end_rad)
	{
		angle = 0;
		while (angle < 360)
		{
			cur.x = info.start_pos.x + cos(ft_deg_to_rad(angle)) * info.beg_rad;
			cur.y = info.start_pos.y + sin(ft_deg_to_rad(angle)) * info.beg_rad;
			if (cur.x >= 0 && cur.x < filler->map->width - piece.width - piece.max_offset.x + 1 &&
				cur.y >= 0 && cur.y < filler->map->height - piece.height - piece.max_offset.y + 1)
			{
				if (test_piece(filler, piece, cur))
				{
					*valid_pos = ft_make_vec2(cur.x, cur.y);
					return (1);
				}
			}
			angle += info.step_angle;
		}
		info.beg_rad++;
	}
	return (0);
}

t_vec2 nearest_opp(t_filler *filler, t_vec2 pos)
{
	t_vec2i cur;
	t_vec2 nearest;
	double d;

	d = INFINITY;

	cur.y = 0;
	while (cur.y < filler->map->height)
	{
		cur.x = 0;
		while (cur.x < filler->map->width)
		{
			if (filler->map->data[cur.y][cur.x] == filler->opp)
			{
				double cur_dist = ft_len_vec2(ft_sub_vec2(ft_make_vec2(cur.x, cur.y), pos));
				if (cur_dist < d)
				{
					d = cur_dist;
					nearest = ft_make_vec2(cur.x, cur.y);
				}
			}
			cur.x++;
		}
		cur.y++;
	}
	return (nearest);
}

t_vec2i spider_strategy(t_filler *filler, t_piece piece)
{
	//t_vec2 dir;
	double angle;


	//t_vec2 pos;
	t_vec2 valid_pos;

	t_vec2 player_start = get_player_start(filler->player, filler);
	//t_vec2 opp_start = get_player_start(filler->opp, filler);
	t_vec2 dir = ft_sub_vec2(nearest_opp(filler, player_start), player_start);
	double len = ft_len_vec2(dir);
	angle = ft_rad_to_deg(atan2(dir.y, dir.x)) - filler->spider_spread / 2;
	valid_pos = ft_make_vec2(0,0);

	if (len > 50)
		return (strategy_fallback(filler, piece));
	//pos.x = player_start.x + cos(ft_deg_to_rad(filler->spider_angle + angle)) * filler->spider_radius;
	//pos.y = player_start.y + sin(ft_deg_to_rad(filler->spider_angle + angle)) * filler->spider_radius;
	t_search_info info;

	info.start_pos = player_start;// ft_add_vec2(player_start, ft_mul_vec2(ft_normalize_vec2(dir), len/2));
	info.beg_rad = 1;
	info.end_rad = 200;
	info.step_angle = 90;
	if (search_radius(filler, piece, info, &valid_pos))
	{
		return (ft_make_vec2i(valid_pos.x, valid_pos.y));
	}

	return (strategy_fallback(filler, piece));
}
