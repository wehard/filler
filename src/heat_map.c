/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:09:33 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/11 16:11:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdlib.h>
#include "debug.h"
#include "libft.h"

t_heat_map	*create_heat_map(int width, int height)
{
	t_heat_map	*heat_map;
	int			i;
	int			size;

	size = width * height;
	heat_map = (t_heat_map*)malloc(sizeof(t_heat_map));
	heat_map->width = width;
	heat_map->height = height;
	heat_map->data = (int*)malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
		heat_map->data[i++] = 10000;
	return (heat_map);
}

double distance_to(t_filler *filler, t_vec2 pos)
{
	t_vec2i	cur;
	double	closest;
	double	dist;

	closest = 1000.0;
	cur.y = 0;
	while (cur.y < filler->map->height)
	{
		cur.x = 0;
		while (cur.x < filler->map->width)
		{
			if (filler->map->data[cur.y][cur.x] == filler->opp)
			{
				dist = ft_len_vec2(ft_sub_vec2(ft_make_vec2(cur.x, cur.y), pos));
				if (dist < closest)
				{
					closest = dist;
				}
			}
			cur.x++;
		}
		cur.y++;
	}
	return (closest);
}

void	update_heat_map(t_filler *filler)
{
	t_vec2i cur;

	cur.y = 0;
	while (cur.y < filler->map->height)
	{
		cur.x = 0;
		while (cur.x < filler->map->width)
		{
			// if (filler->map->data[cur.y][cur.x] == filler->player)
				//filler->heat_map->data[cur.y * filler->map->width + cur.x] = -1;
			// else
				filler->heat_map->data[cur.y * filler->map->width + cur.x] =
					ft_max(1, distance_to(filler, ft_make_vec2(cur.x, cur.y)));
			cur.x++;
		}
		cur.y++;
	}
	//print_heat_map(filler->heat_map->data, filler->map->width, filler->map->height);
}

int		get_score(t_filler *filler, t_vec2i pos)
{
	return (filler->heat_map->data[pos.y * filler->map->width + pos.x]);
}