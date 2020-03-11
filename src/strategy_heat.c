/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_heat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:08:01 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/11 16:03:11 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vector.h"

t_vec2i strategy_heat(t_filler *filler, t_piece piece)
{
	t_vec2i cur;
	t_vec2i best_pos;
	int		best_score;
	int		cur_score;
	int		found_pos;

	//t_vec2 player_start = get_player_start(filler->player, filler);
	//double distance = ft_len_vec2(ft_sub_vec2(nearest_opp(filler, player_start), player_start));
	//if (distance > filler->map->width / 6)
	//	return (strategy_grid(filler, piece));

	update_heat_map(filler);

	found_pos = 0;
	best_score = 1000;
	cur.y = 0;
	while (cur.y < filler->map->height - piece.height - piece.max_offset.y + 1)
	{
		cur.x = 0;
		while (cur.x < filler->map->width - piece.width + piece.max_offset.x + 1)
		{
			cur_score = get_score(filler, cur);
			if (cur_score < 0)
			{
				cur.x++;
				continue ;
			}
			if (test_piece(filler, piece, cur) && cur_score < best_score)
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
	return (strategy_grid(filler, piece));
}
