/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:10:25 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/10 13:45:14 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "vector.h"
#include <math.h>

int	search_radius(t_filler *filler, t_piece piece, t_search_info info, t_vec2 *valid_pos)
{
	t_vec2i cur;
	int angle;

	while (info.beg_rad < info.end_rad)
	{
		angle = 0;
		while (angle < 360)
		{
			cur.x = info.pos.x + cos(ft_deg_to_rad(angle)) * info.beg_rad;
			cur.y = info.pos.y + sin(ft_deg_to_rad(angle)) * info.beg_rad;
			if (cur.x >= 0 && cur.x < filler->map->width - piece.width - piece.max_offset.x + 1 &&
				cur.y >= 0 && cur.y < filler->map->height - piece.height - piece.max_offset.y + 1)
			{
				if (test_piece(filler, piece, cur))
				{
					*valid_pos = ft_make_vec2(cur.x, cur.y);
					return (1);
				}
			}
			angle += info.step_angle;
		}
		info.beg_rad++;
	}
	return (0);
}

int search_area(t_filler *filler, t_piece piece, t_search_info info, t_vec2 *valid_pos)
{
	t_vec2i cur;
	int half_size;

	half_size = info.size / 2;
	cur.y = info.pos.y - half_size;
	if (cur.y < 0)
		cur.y = 0;
	while (cur.y < info.pos.y + half_size && cur.y < filler->map->height - piece.width - piece.max_offset.y + 1)
	{
		cur.x = info.pos.x - half_size;
		if (cur.x < 0)
			cur.x = 0;
		while (cur.x < info.pos.x + half_size && cur.x < filler->map->width - piece.width + piece.max_offset.x + 1)
		{
			if (test_piece(filler, piece, cur))
			{
				*valid_pos = ft_make_vec2(cur.x, cur.y);
					return (1);
			}
			cur.x++;
		}
		cur.y++;
	}
	return (0);
}
