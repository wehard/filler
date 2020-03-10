/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_fallback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:31:57 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/10 11:30:24 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vector.h"
#include "debug.h"

static t_vec2i top_left(t_filler *filler, t_piece piece)
{
	t_vec2i cur;
	t_vec2i end;

	end.y = filler->map->height - piece.height + piece.max_offset.y + 1;
	end.x = filler->map->width - piece.width + piece.max_offset.x + 1;
	cur.y = 0;
	while (cur.y < end.y)
	{
		cur.x = 0;
		while (cur.x < end.x)
		{
			if (test_piece(filler, piece, cur))
				return (cur);
			cur.x++;
		}
		cur.y++;
	}
	return(ft_make_vec2i(-1, -1));
}

static t_vec2i top_right(t_filler *filler, t_piece piece)
{
	t_vec2i cur;
	t_vec2i end;

	end.y = filler->map->height - piece.height + piece.max_offset.y + 1;
	end.x = 0;
	cur.y = 0;
	while (cur.y < end.y)
	{
		cur.x = filler->map->width - piece.width + piece.max_offset.x;
		while (cur.x >= end.x)
		{
			if (test_piece(filler, piece, cur))
				return (cur);
			cur.x--;
		}
		cur.y++;
	}
	return(ft_make_vec2i(-1, -1));
}

static t_vec2i bottom_left(t_filler *filler, t_piece piece)
{
	t_vec2i cur;
	t_vec2i end;

	end.y = 0;
	end.x = filler->map->width - piece.width + piece.max_offset.x + 1;
	cur.y = filler->map->height - piece.height + piece.max_offset.y;
	while (cur.y >= end.y)
	{
		cur.x = 0;
		while (cur.x < end.x)
		{
			if (test_piece(filler, piece, cur))
				return (cur);
			cur.x++;
		}
		cur.y--;
	}
	return(ft_make_vec2i(-1, -1));
}

static t_vec2i bottom_right(t_filler *filler, t_piece piece)
{
	t_vec2i cur;
	t_vec2i end;
	//debug_log("bottom_right\n");
	end.y = 0;
	end.x = 0;
	cur.y = filler->map->height - piece.height + piece.max_offset.y;
	while (cur.y >= end.y)
	{
		cur.x = filler->map->width - piece.width + piece.max_offset.x;
		while (cur.x >= end.x)
		{
			if (test_piece(filler, piece, cur))
				return (cur);
			cur.x--;
		}
		cur.y--;
	}
	return(ft_make_vec2i(-1, -1));
}

int		check_opp_fill(t_filler *filler, int res)
{
	t_vec2i cur;
	int		fill[4];
	int		quadrant;
	int		i;

	quadrant = 0;
	fill[0] = 0;
	fill[1] = 0;
	fill[2] = 0;
	fill[3] = 0;
	cur.y = 0;
	while (cur.y < filler->map->height)
	{
		cur.x = 0;
		while (cur.x < filler->map->width)
		{
			if (cur.x < filler->map->width / 2 && cur.y < filler->map->height / 2)
				quadrant = 0;
			if (cur.x > filler->map->width / 2 && cur.y < filler->map->height / 2)
				quadrant = 1;
			if (cur.x < filler->map->width / 2 && cur.y > filler->map->height / 2)
				quadrant = 2;
			if (cur.x > filler->map->width / 2 && cur.y > filler->map->height / 2)
				quadrant = 3;
			if (filler->map->data[cur.y][cur.x] == filler->opp)
				fill[quadrant]++;
			cur.x += res;
		}
		cur.y += res;
	}
	int w;

	w = -1;
	i = 0;
	while (i < 4)
	{
		if (fill[i] > w)
		{
			quadrant = i;
			w = fill[i];
		}
		i++;
	}
	return (quadrant);
}

t_vec2i strategy_fallback(t_filler *filler, t_piece piece)
{
	//t_vec2 player_start = get_player_start(filler->player, filler);
	//t_vec2 opp_start = get_player_start(filler->opp, filler);
	//t_vec2 dir = ft_normalize_vec2(ft_sub_vec2(opp_start, player_start));

	int f = check_opp_fill(filler, 10);

	if (f == 0)
		return (top_left(filler, piece));
	if (f == 1)
		return (top_right(filler, piece));
	if (f == 2)
		return (bottom_left(filler, piece));
	if (f == 3)
		return (bottom_right(filler, piece));


	/* if (dir.x < 0)
	{
		if (dir.y < 0)
			return (top_left(filler, piece));
		else
			return (bottom_left(filler, piece));
	}
	else
	{
		if (dir.y < 0)
			return (top_right(filler, piece));
		else
			return (bottom_right(filler, piece));
	} */
	return (ft_make_vec2i(-1, -1));
}
