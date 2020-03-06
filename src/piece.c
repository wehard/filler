/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:32:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/06 17:40:22 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vector.h"
#include "debug.h"
#include <stdlib.h>

int left_offset(t_piece p)
{
	t_vec2i cur;

	cur.x = 0;
	while (cur.x < p.width)
	{
		cur.y = 0;
		while (cur.y < p.height)
		{
			if (p.data[cur.y][cur.x] == ASTERISK)
				return (cur.x);
			cur.y++;
		}
		cur.x++;
	}
	return (0);
}

int right_offset(t_piece p)
{
	t_vec2i cur;

	cur.x = p.width - 1;
	while (cur.x >= 0)
	{
		cur.y = 0;
		while (cur.y < p.height)
		{
			if (p.data[cur.y][cur.x] == ASTERISK)
				return (p.width - cur.x - 1);
			cur.y++;
		}
		cur.x--;
	}
	return (0);
}

int top_offset(t_piece p)
{
	t_vec2i cur;

	cur.y = 0;
	while (cur.y < p.height)
	{
		cur.x = 0;
		while (cur.x < p.width)
		{
			if (p.data[cur.y][cur.x] == ASTERISK)
				return (cur.y);
			cur.x++;
		}
		cur.y++;
	}
	return (0);
}

int bottom_offset(t_piece p)
{
	t_vec2i cur;

	cur.y = p.height - 1;
	while (cur.y >= 0)
	{
		cur.x = 0;
		while (cur.x < p.width)
		{
			if (p.data[cur.y][cur.x] == ASTERISK)
				return (p.height - cur.y - 1);
			cur.x++;
		}
		cur.y--;
	}
	return (0);
}

t_vec2i calc_piece_min_offset(t_piece piece)
{
	t_vec2i offset;

	offset.x = left_offset(piece);
	offset.y = top_offset(piece);
	debug_log("piece min offset: r%d c%d\n", offset.y, offset.x);
	return (offset);
}

t_vec2i calc_piece_max_offset(t_piece piece)
{
	t_vec2i offset;

	offset.x = right_offset(piece);
	offset.y = bottom_offset(piece);
	debug_log("piece max offset: r%d c%d\n", offset.y, offset.x);
	return (offset);
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
	//t_vec2i c = calc_top_left_corner(*piece);
	//debug_log("corner: %d %d", c.x, c.y);
	piece->min_offset = calc_piece_min_offset(*piece);
	piece->max_offset = calc_piece_max_offset(*piece);
	return (piece);
}


