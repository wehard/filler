/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:09:33 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/12 14:23:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdlib.h>
#include "debug.h"
#include "libft.h"

t_heat_map		*create_heat_map(int width, int height)
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

static double	distance_to(t_filler *filler, t_vec2 pos)
{
	t_vec2i	cur;
	double	closest;
	double	d;

	closest = 1000.0;
	cur.y = 0;
	while (cur.y < filler->map->height)
	{
		cur.x = 0;
		while (cur.x < filler->map->width)
		{
			if (filler->map->data[cur.y][cur.x] == filler->opp)
			{
				d = ft_len_vec2(ft_sub_vec2(ft_make_vec2(cur.x, cur.y), pos));
				if (d < closest)
				{
					closest = d;
				}
			}
			cur.x++;
		}
		cur.y++;
	}
	return (closest);
}

static int		discard(t_filler *filler, t_vec2i pos)
{
	t_map *map;

	map = filler->map;
	if (pos.y > 0 && map->data[pos.y - 1][pos.x] == filler->opp &&
		pos.y < map->height - 1 && map->data[pos.y + 1][pos.x] == filler->opp &&
		pos.x > 0 && map->data[pos.y][pos.x - 1] == filler->opp &&
		pos.x < map->width - 1 && map->data[pos.y][pos.x + 1] == filler->opp)
		return (1);
	return (0);
}

int				get_score(t_filler *filler, t_vec2i pos)
{
	return (filler->heat_map->data[pos.y * filler->map->width + pos.x]);
}

void			update_heat_map(t_filler *filler)
{
	t_vec2i		cur;
	t_map		*map;
	t_heat_map	*hmap;

	map = filler->map;
	hmap = filler->heat_map;
	cur.y = 0;
	while (cur.y < map->height)
	{
		cur.x = 0;
		while (cur.x < map->width)
		{
			if (hmap->data[cur.y * map->width + cur.x] == -1 ||
					discard(filler, cur))
				hmap->data[cur.y * map->width + cur.x] = -1;
			else
				hmap->data[cur.y * filler->map->width + cur.x] =
					ft_max(1, distance_to(filler, ft_make_vec2(cur.x, cur.y)));
			cur.x++;
		}
		cur.y++;
	}
}
