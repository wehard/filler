/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 20:20:14 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/10 22:35:57 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

t_map *create_map(int width, int height)
{
	t_map *map;
	int y;

	map = (t_map*)malloc(sizeof(t_map));
	map->width = width;
	map->height = height;
	map->data = (char**)malloc(sizeof(char*) * height);
	y = 0;
	while (y < height)
	{
		map->data[y] = (char*)malloc(sizeof(char) * width);
		ft_bzero(map->data[y], width);
		y++;
	}
	ft_printf("created map r%d c%d\n", height, width);
	return (map);
}
