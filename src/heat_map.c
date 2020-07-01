/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:09:33 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/01 14:56:10 by wkorande         ###   ########.fr       */
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

static int	distance_to(t_filler *filler, t_vec2 pos)
{
	t_vec2i	cur;
	int	closest;
	t_vec2i	d;

	closest = 100000;
	cur.y = 0;
	while (cur.y < filler->map->height)
	{
		cur.x = 0;
		while (cur.x < filler->map->width)
		{
			if (filler->map->data[cur.y][cur.x] == filler->opp)
			{
				d.x = cur.x < pos.x ? pos.x - cur.x : cur.x - pos.x;
				d.y = cur.y < pos.y ? pos.y - cur.y : cur.y - pos.y;
				if (d.x + d.y < closest)
				{
					closest = d.x + d.y;
				}
			}
			cur.x++;
		}
		cur.y++;
	}
	return (closest);
}

// static int		discard(t_filler *filler, t_vec2i pos)
// {
// 	t_map *map;

// 	map = filler->map;
// 	if (pos.y > 0 && map->data[pos.y - 1][pos.x] == filler->opp &&
// 		pos.y < map->height - 1 && map->data[pos.y + 1][pos.x] == filler->opp &&
// 		pos.x > 0 && map->data[pos.y][pos.x - 1] == filler->opp &&
// 		pos.x < map->width - 1 && map->data[pos.y][pos.x + 1] == filler->opp)
// 		return (0);
// 	return (0);
// }

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
			// if (hmap->data[cur.y * map->width + cur.x] == -1 ||
			// 		discard(filler, cur))
			// 	hmap->data[cur.y * map->width + cur.x] = -1;
			// else
			hmap->data[cur.y * filler->map->width + cur.x] =
				distance_to(filler, ft_make_vec2(cur.x, cur.y));
			cur.x++;
		}
		cur.y++;
	}
}
