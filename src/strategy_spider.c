/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_spider.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:09:13 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/12 11:55:43 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "vector.h"
#include "debug.h"
#include <math.h>

t_vec2 nearest_opp(t_filler *filler, t_vec2 pos)
{
	t_vec2i cur;
	t_vec2 nearest;
	double d;

	d = 99999.0;

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


t_vec2i strategy_spider(t_filler *filler, t_piece piece)
{
	//t_vec2 dir;
	//double angle;


	//t_vec2 pos;
	t_vec2 valid_pos;

	t_vec2 player_start = get_player_start(filler->player, filler);
	//t_vec2 opp_start = get_player_start(filler->opp, filler);
	t_vec2 dir = ft_sub_vec2(nearest_opp(filler, player_start), player_start);
	double len = ft_len_vec2(dir);
	//angle = ft_rad_to_deg(atan2(dir.y, dir.x)) - filler->spider_spread / 2;
	valid_pos = ft_make_vec2(0,0);

	if (len > 50)
		return (strategy_fallback(filler, piece));
	//pos.x = player_start.x + cos(ft_deg_to_rad(filler->spider_angle + angle)) * filler->spider_radius;
	//pos.y = player_start.y + sin(ft_deg_to_rad(filler->spider_angle + angle)) * filler->spider_radius;
	t_search_info info;

	info.pos = player_start;// ft_add_vec2(player_start, ft_mul_vec2(ft_normalize_vec2(dir), len/2));
	info.beg_rad = 1;
	info.end_rad = 200;
	info.step_angle = 90;
	if (search_radius(filler, piece, info, &valid_pos))
	{
		return (ft_make_vec2i(valid_pos.x, valid_pos.y));
	}
	return (strategy_fallback(filler, piece));
}
