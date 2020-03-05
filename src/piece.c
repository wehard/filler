/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:32:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/05 23:14:27 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vector.h"
#include "debug.h"
#include <stdlib.h>

t_vec2i calc_top_left_corner(t_piece piece)
{
	t_vec2i cur;
	t_vec2i corner;

	corner.x = 0;
	corner.y = 0;
	cur.y = 0;
	while (cur.y < piece.height)
	{
		cur.x = 0;
		while (cur.x < piece.width)
		{
			if (piece.data[cur.y][cur.x] == ASTERISK)
			{
				corner = cur;
				return (corner);
			}
			cur.x++;
		}
		cur.y++;
	}
	// check errors
	return (corner);
}

t_piece *read_piece(int width, int height)
{
	t_piece *piece;

	piece = (t_piece*)malloc(sizeof(t_piece));
	piece->height = height;
	piece->width =  width;
	if (piece->width < 1 || piece->height < 1)
	{
		ft_panic("error: bad piece dimensions!");
		return (NULL);
	}
	piece->data = make_area(piece->width, piece->height);
	populate_area(piece->data, piece->width, piece->height, 0);
	t_vec2i c = calc_top_left_corner(*piece);
	debug_log2("corner: %d %d\n", c.x, c.y);
	return (piece);
}


