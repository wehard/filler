/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_circ_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 19:07:41 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/07 13:18:00 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_vec2i	strategy_circ_search(t_filler *filler, t_piece *piece)
{
	t_search_info	info;
	t_vec2			valid_pos;

	info.pos = ft_make_vec2(filler->player_last.x, filler->player_last.y);
	info.start_angle = 0;
	info.end_angle = 360;
	info.beg_rad = 3;
	info.end_rad = 10;
	info.step_angle = 2;
	if (search_radius(filler, piece, info, &valid_pos))
		return (ft_make_vec2i(valid_pos.x, valid_pos.y));
	return (strategy_heat(filler, piece));
}
