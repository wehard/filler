/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_offset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 14:35:19 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/14 20:32:04 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	left_offset(t_piece p)
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

static int	right_offset(t_piece p)
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

static int	top_offset(t_piece p)
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

static int	bottom_offset(t_piece p)
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

void		calc_piece_offset(t_piece *pc)
{
	pc->min_offset.x = left_offset(*pc);
	pc->min_offset.y = top_offset(*pc);
	pc->max_offset.x = right_offset(*pc);
	pc->max_offset.y = bottom_offset(*pc);
	pc->act_size.x = pc->width - pc->min_offset.x - pc->max_offset.x;
	pc->act_size.y = pc->height - pc->min_offset.y - pc->max_offset.y;
}
