/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:10:25 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/10 16:39:46 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "vector.h"
#include <math.h>

int		search_radius(t_filler *f, t_piece *pc,
	t_search_info info, t_vec2 *valid_pos)
{
	t_vec2i	cur;
	int		angle;

	while (info.beg_rad < info.end_rad)
	{
		angle = info.start_angle;
		while (angle < info.end_angle)
		{
			cur.x = info.pos.x + cos(ft_deg_to_rad(angle)) * info.beg_rad;
			cur.y = info.pos.y + sin(ft_deg_to_rad(angle)) * info.beg_rad;
			if (cur.x >= 0 && cur.x < f->map->width - pc->width -
				pc->max_offset.x + 1 && cur.y >= 0 && cur.y <
				f->map->height - pc->height - pc->max_offset.y + 1)
			{
				if (test_piece(f, pc, cur))
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

int		search_area(t_filler *f, t_piece *pc,
	t_search_info info, t_vec2 *valid_pos)
{
	t_vec2i	cur;
	int		half_size;

	half_size = info.size / 2;
	cur.y = info.pos.y - half_size;
	cur.y < 0 ? (cur.y = 0) : 0;
	while (cur.y < info.pos.y + half_size &&
		cur.y < f->map->height - pc->width - pc->max_offset.y + 1)
	{
		cur.x = info.pos.x - half_size;
		if (cur.x < 0)
			cur.x = 0;
		while (cur.x < info.pos.x + half_size &&
			cur.x < f->map->width - pc->width + pc->max_offset.x + 1)
		{
			if (test_piece(f, pc, cur))
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
