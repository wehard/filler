/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:07:46 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/10 16:02:57 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vector.h"
#include "debug.h"
#include <math.h>

t_vec2i	top_left(t_filler *f, t_piece *pc, int size, t_search_info info)
{
	t_vec2i	cur;
	t_vec2	valid_pos;

	cur.y = 0;
	while (cur.y < f->map->height - pc->width - pc->max_offset.y + 1)
	{
		cur.x = 0;
		while (cur.x < f->map->width - pc->width + pc->max_offset.x + 1)
		{
			info.pos = ft_make_vec2(cur.x, cur.y);
			if (search_radius(f, pc, info, &valid_pos))
				return (ft_make_vec2i(valid_pos.x, valid_pos.y));
			cur.x += size;
		}
		cur.y += size;
	}
	return (strategy_fallback(f, pc));
}

t_vec2i	top_right(t_filler *f, t_piece *p, int size, t_search_info info)
{
	t_vec2i	cur;
	t_vec2	valid_pos;

	cur.y = 0;
	while (cur.y < f->map->height - p->width - p->max_offset.y + 1)
	{
		cur.x = f->map->width;
		while (cur.x >= 0)
		{
			info.pos = ft_make_vec2(cur.x, cur.y);
			if (search_radius(f, p, info, &valid_pos))
				return (ft_make_vec2i(valid_pos.x, valid_pos.y));
			cur.x -= size;
		}
		cur.y += size;
	}
	return (strategy_fallback(f, p));
}

t_vec2i	bottom_right(t_filler *f, t_piece *pc, int size, t_search_info info)
{
	t_vec2i	cur;
	t_vec2	valid_pos;

	cur.y = f->map->height;
	while (cur.y >= 0)
	{
		cur.x = f->map->width;
		while (cur.x >= 0)
		{
			info.pos = ft_make_vec2(cur.x, cur.y);
			if (search_radius(f, pc, info, &valid_pos))
				return (ft_make_vec2i(valid_pos.x, valid_pos.y));
			cur.x -= size;
		}
		cur.y -= size;
	}
	return (strategy_fallback(f, pc));
}

t_vec2i	bottom_left(t_filler *f, t_piece *pc, int size, t_search_info info)
{
	t_vec2i	cur;
	t_vec2	valid_pos;

	cur.y = f->map->height;
	while (cur.y >= 0)
	{
		cur.x = 0;
		while (cur.x < f->map->width - pc->width + pc->max_offset.x + 1)
		{
			info.pos = ft_make_vec2(cur.x, cur.y);
			if (search_radius(f, pc, info, &valid_pos))
				return (ft_make_vec2i(valid_pos.x, valid_pos.y));
			cur.x += size;
		}
		cur.y -= size;
	}
	return (strategy_fallback(f, pc));
}

t_vec2i	strategy_grid(t_filler *f, t_piece *pc)
{
	t_search_info	info;
	t_vec2i			pl_start;
	t_vec2i			opp_start;
	t_vec2i			dir;
	t_vec2i			pos;

	pl_start = get_player_start(f->pl, f);
	opp_start = get_player_start(f->opp, f);
	dir = ft_make_vec2i(opp_start.x - pl_start.x, opp_start.y - pl_start.y);
	info.beg_rad = 0;
	info.end_rad = 20;
	info.start_angle = atan2(dir.y, dir.x) * 180 / 3.14;
	info.end_angle = info.start_angle + 360;
	info.step_angle = 90;
	if (dir.y < 0)
	{
		dir.x < 0 ? (pos = top_left(f, pc, f->grid_size, info)) :
			(pos = top_right(f, pc, f->grid_size, info));
	}
	else
	{
		dir.x < 0 ? (pos = bottom_left(f, pc, f->grid_size, info)) :
			(pos = bottom_right(f, pc, f->grid_size, info));
	}
	return (pos);
}
