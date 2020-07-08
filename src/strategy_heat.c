/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_heat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:08:01 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/08 15:02:04 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vector.h"
#include "debug.h"


int		piece_score(t_filler *filler, t_piece *piece, t_vec2i pos)
{
	int score;
	t_vec2i p;
	t_vec2i piece_size;
	t_vec2i m;

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
			score += get_score(filler, m);
			p.x++;
			m.x++;
		}
		p.y++;
		m.y++;
	}
	return (score);
}

t_vec2i strategy_heat(t_filler *filler, t_piece *piece)
{
	t_vec2i cur;
	t_vec2i best_pos;
	int		best_score;
	int		cur_score;
	int		found_pos;

	t_vec2i piece_size;

	piece_size.x = piece->width - piece->min_offset.x - piece->max_offset.x;
	piece_size.y = piece->height - piece->min_offset.y - piece->max_offset.y;

	update_heat_map(filler);
	found_pos = 0;
	best_score = 10000;
	cur.y = 0;
	while (cur.y < filler->map->height - piece_size.y + 1)
	{
		cur.x = 0;
		while (cur.x < filler->map->width - piece_size.x + 1)
		{
			cur_score = piece_score(filler, piece, cur);
			if (cur_score < best_score && test_piece(filler, piece, cur))
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
