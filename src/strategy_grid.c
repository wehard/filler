/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:07:46 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/25 18:07:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vector.h"
#include "debug.h"


t_vec2i top_left(t_filler *filler, t_piece *piece, int grid_size, t_search_info info)
{
	t_vec2i cur;
	t_vec2 valid_pos;
	//t_vec2 player_start;

	//player_start = get_player_start(filler->player, filler);
	cur.y = 0; // (int)player_start.y % grid_size;
	while (cur.y < filler->map->height - piece->width - piece->max_offset.y + 1)
	{
		cur.x = 0; // (int)player_start.x % grid_size;
		while (cur.x < filler->map->width - piece->width + piece->max_offset.x + 1)
		{

			info.pos = ft_make_vec2(cur.x, cur.y);
			if (search_radius(filler, piece, info, &valid_pos))
				return (ft_make_vec2i(valid_pos.x, valid_pos.y));
			cur.x += grid_size;
		}
		cur.y += grid_size;
	}
	return (strategy_fallback(filler, piece));
}

t_vec2i top_right(t_filler *filler, t_piece *piece, int grid_size, t_search_info info)
{
	t_vec2i cur;
	t_vec2 valid_pos;
	//t_vec2 player_start;

	//player_start = get_player_start(filler->player, filler);
	cur.y = 0; // (int)player_start.y % grid_size;
	while (cur.y < filler->map->height - piece->width - piece->max_offset.y + 1)
	{
		cur.x = filler->map->width; // (int)player_start.x % grid_size;
		while (cur.x >= 0)
		{

			info.pos = ft_make_vec2(cur.x, cur.y);
			if (search_radius(filler, piece, info, &valid_pos))
				return (ft_make_vec2i(valid_pos.x, valid_pos.y));
			cur.x -= grid_size;
		}
		cur.y += grid_size;
	}
	return (strategy_fallback(filler, piece));
}

t_vec2i bottom_right(t_filler *filler, t_piece *piece, int grid_size, t_search_info info)
{
	t_vec2i cur;
	t_vec2 valid_pos;
	//t_vec2 player_start;

	//player_start = get_player_start(filler->player, filler);
	cur.y = filler->map->height; //- (int)player_start.y % grid_size;
	while (cur.y >= 0)
	{
		cur.x = filler->map->width; // - (int)player_start.x % grid_size;
		while (cur.x >= 0)
		{
			info.pos = ft_make_vec2(cur.x, cur.y);
			if (search_radius(filler, piece, info, &valid_pos))
				return (ft_make_vec2i(valid_pos.x, valid_pos.y));
			cur.x -= grid_size;
		}
		cur.y -= grid_size;
	}
	return (strategy_fallback(filler, piece));
}

t_vec2i bottom_left(t_filler *filler, t_piece *piece, int grid_size, t_search_info info)
{
	t_vec2i cur;
	t_vec2 valid_pos;
	//t_vec2 player_start;

	//player_start = get_player_start(filler->player, filler);
	cur.y = filler->map->height; // - (int)player_start.y % grid_size;
	while (cur.y >= 0)
	{
		cur.x = 0; //(int)player_start.x % grid_size;
		while (cur.x < filler->map->width - piece->width + piece->max_offset.x + 1)
		{
			info.pos = ft_make_vec2(cur.x, cur.y);
			if (search_radius(filler, piece, info, &valid_pos))
				return (ft_make_vec2i(valid_pos.x, valid_pos.y));
			cur.x += grid_size;
		}
		cur.y -= grid_size;
	}
	return (strategy_fallback(filler, piece));
}

t_vec2i strategy_grid(t_filler *filler, t_piece *piece)
{
	t_search_info info;

	int grid_size = filler->grid_size;
	info.beg_rad = 3;
	info.end_rad = 20;
	info.step_angle = 90;

	t_vec2 player_start = get_player_start(filler->player, filler);
	t_vec2 opp_start = get_player_start(filler->opp, filler);
	t_vec2 dir = ft_normalize_vec2(ft_sub_vec2(opp_start, player_start));
	// double distance = ft_len_vec2(ft_sub_vec2(search_opp(filler, player_start), player_start));
	// if (distance > filler->map->width / 6)
	// 	return (strategy_fallback(filler, piece));


	// int f = check_opp_fill(filler, 16);
	// if (f == 0)
	// 	dir = ft_make_vec2(-1,-1);
	// if (f == 1)
	// 	dir = ft_make_vec2(1,-1);
	// if (f == 2)
	// 	dir = ft_make_vec2(-1,1);
	// if (f == 3)
	// 	dir = ft_make_vec2(1,1);

	if (dir.y < 0)
	{
		if (dir.x < 0)
			return (top_left(filler, piece, grid_size, info));
		else
			return (top_right(filler, piece, grid_size, info));
	}
	else
	{
		if (dir.x < 0)
			return (bottom_left(filler, piece, grid_size, info));
		else
			return (bottom_right(filler, piece, grid_size, info)); //return (top_right(filler, piece, grid_size, info));
	}
	return (strategy_fallback(filler, piece));
}
