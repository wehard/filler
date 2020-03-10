/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:07:46 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/10 14:36:27 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vector.h"
#include "debug.h"

t_vec2i strategy_grid(t_filler *filler, t_piece piece)
{
	t_vec2i cur;
	t_vec2 valid_pos;
	int grid_size = 15;
	t_vec2 player_start = get_player_start(filler->player, filler);


	cur.y = (int)player_start.y % grid_size;
	//debug_log("cury: %d\n", cur.y);
	while (cur.y < filler->map->height - piece.width - piece.max_offset.y + 1)
	{
		cur.x = (int)player_start.x % grid_size;
		while (cur.x < filler->map->width - piece.width + piece.max_offset.x + 1)
		{
			t_search_info info;
			info.beg_rad = 1;
			info.end_rad = 15;
			info.size = 15;
			info.step_angle = 90;
			info.pos = ft_make_vec2(cur.x, cur.y);
			if (search_radius(filler, piece, info, &valid_pos))
				return (ft_make_vec2i(valid_pos.x, valid_pos.y));
			cur.x += grid_size;
		}
		cur.y += grid_size;
	}
	return (strategy_fallback(filler, piece));
}
