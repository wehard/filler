/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_heat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:08:01 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/30 15:47:36 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vector.h"
#include "debug.h"

t_vec2i strategy_heat(t_filler *filler, t_piece *piece)
{
	t_vec2i cur;
	t_vec2i best_pos;
	int		best_score;
	int		cur_score;
	int		found_pos;

	//t_vec2 player_start = get_player_start(filler->player, filler);
	//double distance = ft_len_vec2(ft_sub_vec2(nearest_opp(filler, player_start), player_start));

	int threshold = 0;
	// if (filler->turn %  == 0)
		update_heat_map(filler);
	found_pos = 0;
	best_score = 1000;
	cur.y = 0;
	while (cur.y < filler->map->height - piece->height - piece->max_offset.y + 1)
	{
		cur.x = 0;
		while (cur.x < filler->map->width - piece->width + piece->max_offset.x + 1)
		{
			cur_score = get_score(filler, cur);
			if (cur_score < 0)
			{
				cur.x++;
				continue ;
			}
			// fix score with map size
			//
			// debug_log("threshold: %d\n", threshold);
			if (cur_score > threshold && cur_score < best_score && test_piece(filler, piece, cur))
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
	return (strategy_fallback(filler, piece));
}
