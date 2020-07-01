/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:32:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/01 13:34:43 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
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
	return (offset);
}

t_vec2i calc_piece_max_offset(t_piece piece)
{
	t_vec2i offset;

	offset.x = right_offset(piece);
	offset.y = bottom_offset(piece);
	return (offset);
}

t_piece *read_piece(char *line)
{
	t_piece *piece;
	char **split;

	if (!(piece = (t_piece*)malloc(sizeof(t_piece))))
		ft_panic("read_piece: malloc failed!");
	split = ft_strsplit(line, ' ');
	piece->height = ft_atoi(split[1]);
	piece->width =  ft_atoi(split[2]);
	if (piece->width < 1 || piece->height < 1)
		ft_panic("error: bad piece dimensions!");
	piece->data = make_area(piece->width, piece->height);
	populate_area(piece->data, piece->width, piece->height, 0);
	piece->min_offset = calc_piece_min_offset(*piece);
	piece->max_offset = calc_piece_max_offset(*piece);
	return (piece);
}

int	test_piece(t_filler *filler, t_piece *piece, t_vec2i pos)
{
	int num_overlap;
	t_vec2i m;
	t_vec2i p;

	if (pos.x == 1 && pos.y == 20)
	{
		debug_log(".\n");
	}

	num_overlap = 0;
	p.y = piece->min_offset.y;
	m.y = pos.y;
	while (p.y < piece->height - piece->max_offset.y)
	{
		p.x = piece->min_offset.x;
		m.x = pos.x;
		while (p.x < piece->width - piece->max_offset.x)
		{
			if (piece->data[p.y][p.x] == ASTERISK && filler->map->data[m.y][m.x] == filler->opp)
				return (0);
			if (piece->data[p.y][p.x] == ASTERISK && filler->map->data[m.y][m.x] == filler->player)
				num_overlap++;
			//if (num_overlap > 1)
			//	return (0);
			p.x++;
			m.x++;
		}
		p.y++;
		m.y++;
	}
	return (num_overlap == 1);
}

