/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_fallback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:31:57 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/01 17:20:33 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vector.h"
#include "debug.h"
#include "libft.h"

static t_vec2i top_left(t_filler *filler, t_piece *piece)
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
	print_area(piece->data, piece->width, piece->height);
	print_area(filler->map->data, filler->map->width, filler->map->height);
	return(ft_make_vec2i(-99, -99));
}

static t_vec2i top_right(t_filler *filler, t_piece *piece)
{
	t_vec2i cur;
	t_vec2i end;
	t_vec2i piece_size;

	piece_size.x = piece->width - piece->min_offset.x - piece->max_offset.x;
	piece_size.y = piece->height - piece->min_offset.y - piece->max_offset.y;

	end.y = filler->map->height - piece_size.y;
	end.x = 0;
	cur.y = 0;
	while (cur.y <= end.y)
	{
		cur.x = filler->map->width - piece_size.x;
		while (cur.x >= end.x)
		{
			if (test_piece(filler, piece, cur))
				return (cur);
			cur.x--;
		}
		cur.y++;
	}
	debug_log("top_right: fallback failed!\n");
	print_area(piece->data, piece->width, piece->height);
	return(ft_make_vec2i(-1, -1));
}

static t_vec2i bottom_left(t_filler *filler, t_piece *piece)
{
	t_vec2i cur;
	t_vec2i end;
	t_vec2i piece_size;

	piece_size.x = piece->width - piece->min_offset.x - piece->max_offset.x;
	piece_size.y = piece->height - piece->min_offset.y - piece->max_offset.y;

	end.y = 0;
	end.x = filler->map->width - piece_size.x;
	cur.y = filler->map->height - piece_size.y;
	while (cur.y >= end.y)
	{
		cur.x = 0;
		while (cur.x <= end.x)
		{
			if (test_piece(filler, piece, cur))
				return (cur);
			cur.x++;
		}
		cur.y--;
	}
	debug_log("bottom_left: fallback failed!\n");
	print_area(piece->data, piece->width, piece->height);
	return(ft_make_vec2i(-1, -1));
}

static t_vec2i bottom_right(t_filler *filler, t_piece *piece)
{
	t_vec2i cur;
	t_vec2i end;
	t_vec2i piece_size;

	piece_size.x = piece->width - piece->min_offset.x - piece->max_offset.x;
	piece_size.y = piece->height - piece->min_offset.y - piece->max_offset.y;

	end.y = 0;
	end.x = 0;
	cur.y = filler->map->height - piece_size.y;
	while (cur.y >= end.y)
	{
		cur.x = filler->map->width - piece_size.x;
		while (cur.x >= end.x)
		{
			if (test_piece(filler, piece, cur))
				return (cur);
			cur.x--;
		}
		cur.y--;
	}
	debug_log("bottom_right: fallback failed!\n");
	print_area(piece->data, piece->width, piece->height);
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

t_vec2i strategy_fallback(t_filler *filler, t_piece *piece)
{
	debug_log("fallback\n");
	return (top_left(filler, piece));
}

t_vec2i strategy_fallback_dir(t_filler *filler, t_piece *piece, int dir)
{
	if (dir == DIR_TOPLEFT)
		return (top_left(filler, piece));
	else if (dir == DIR_BOTTOMLEFT)
		return (bottom_left(filler, piece));
	else if (dir == DIR_TOPRIGHT)
		return (top_right(filler, piece));
	else if (dir == DIR_BOTTOMRIGHT)
		return (bottom_right(filler, piece));
	return (ft_make_vec2i(-999, -999));
}
