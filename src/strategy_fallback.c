/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_fallback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:31:57 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/09 18:13:50 by wkorande         ###   ########.fr       */
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

t_vec2i strategy_fallback(t_filler *filler, t_piece piece)
{
	t_vec2 player_start = get_player_start(filler->player, filler);
	t_vec2 opp_start = get_player_start(filler->opp, filler);
	t_vec2 dir = ft_normalize_vec2(ft_sub_vec2(opp_start, player_start));
	//debug_log("dir x%.2f y%.2f\n", dir.x, dir.y);
	if (dir.x < 0)
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
	}
	return (ft_make_vec2i(-1, -1));
}
