/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_fallback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:31:57 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/07 14:56:24 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vector.h"
#include "debug.h"
#include "libft.h"

t_vec2i	strategy_fallback(t_filler *filler, t_piece *piece)
{
	t_vec2i cur;
	t_vec2i end;
	t_vec2i piece_size;

	piece_size.x = piece->width - piece->min_offset.x - piece->max_offset.x;
	piece_size.y = piece->height - piece->min_offset.y - piece->max_offset.y;
	end.y = filler->map->height - piece_size.y;
	end.x = filler->map->width - piece_size.x;
	cur.y = 0;
	while (cur.y <= end.y)
	{
		cur.x = 0;
		while (cur.x <= end.x)
		{
			if (test_piece(filler, piece, cur))
				return (cur);
			cur.x++;
		}
		cur.y++;
	}
	return (ft_make_vec2i(0, 0));
}
