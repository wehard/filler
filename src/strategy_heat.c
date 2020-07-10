/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_heat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:08:01 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/10 16:19:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vector.h"
#include "debug.h"
#include <stdlib.h>

t_heat_map	*create_heat_map(int width, int height)
{
	t_heat_map	*heat_map;
	int			i;
	int			size;

	size = width * height;
	heat_map = (t_heat_map*)malloc(sizeof(t_heat_map));
	heat_map->width = width;
	heat_map->height = height;
	heat_map->data = (int*)malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
		heat_map->data[i++] = 10000;
	return (heat_map);
}

int			get_dist_closest_opp(t_filler *filler, t_vec2i pos)
{
	t_vec2i	cur;
	int		closest;
	t_vec2i	d;

	closest = 100000;
	cur.y = 0;
	while (cur.y < filler->map->height)
	{
		cur.x = 0;
		while (cur.x < filler->map->width)
		{
			if (filler->map->data[cur.y][cur.x] == filler->opp)
			{
				d.x = cur.x < pos.x ? pos.x - cur.x : cur.x - pos.x;
				d.y = cur.y < pos.y ? pos.y - cur.y : cur.y - pos.y;
				if (d.x + d.y < closest)
				{
					closest = d.x + d.y;
				}
			}
			cur.x++;
		}
		cur.y++;
	}
	return (closest);
}

void		update_heat_map(t_filler *filler)
{
	t_vec2i		cur;
	t_map		*map;
	t_heat_map	*hmap;

	map = filler->map;
	hmap = filler->heat_map;
	cur.y = 0;
	while (cur.y < map->height)
	{
		cur.x = 0;
		while (cur.x < map->width)
		{
			hmap->data[cur.y * filler->map->width + cur.x] =
				get_dist_closest_opp(filler, cur);
			cur.x++;
		}
		cur.y++;
	}
}

int			piece_score(t_filler *filler, t_piece *piece, t_vec2i pos)
{
	int		score;
	t_vec2i	p;
	t_vec2i	piece_size;
	t_vec2i	m;

	piece_size.x = piece->width - piece->min_offset.x - piece->max_offset.x;
	piece_size.y = piece->height - piece->min_offset.y - piece->max_offset.y;
	score = 0;
	m.y = pos.y;
	p.y = piece->height - piece->min_offset.y;
	while (m.y < pos.y + piece_size.y)
	{
		m.x = pos.x;
		p.x = piece->width - piece->min_offset.x;
		while (m.x < pos.x + piece_size.x)
		{
			score += filler->heat_map->data[m.y * filler->map->width + m.x];
			p.x++;
			m.x++;
		}
		p.y++;
		m.y++;
	}
	return (score);
}

t_vec2i		strategy_heat(t_filler *filler, t_piece *pc)
{
	t_vec2i cur;
	t_vec2i best_pos;
	int		best_score;
	int		cur_score;
	int		found_pos;
	t_vec2i pc_size;

	pc_size.x = pc->width - pc->min_offset.x - pc->max_offset.x;
	pc_size.y = pc->height - pc->min_offset.y - pc->max_offset.y;
	update_heat_map(filler);
	found_pos = 0;
	best_score = 10000;
	cur.y = 0;
	while (cur.y < filler->map->height - pc_size.y + 1)
	{
		cur.x = 0;
		while (cur.x < filler->map->width - pc_size.x + 1)
		{
			cur_score = piece_score(filler, pc, cur);
			if (cur_score < best_score && test_piece(filler, pc, cur))
			{
				best_pos = cur;
				best_score = cur_score;
				found_pos = 1;
			}
			cur.x++;
		}
		cur.y++;
	}
	if (found_pos)
		return (best_pos);
	return (strategy_fallback(filler, pc));
}
