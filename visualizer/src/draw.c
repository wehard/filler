/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:50:23 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/18 22:11:59 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	draw_tile(t_env *env, t_vec2i pos, int size, int color)
{
	t_vec2i cur;

	cur.y = pos.y + 1;
	while (cur.y < pos.y + size - 1)
	{
		cur.x = pos.x + 1;
		while (cur.x < pos.x + size - 1)
		{
			put_pixel_mlx_img(env->mlx_img, cur.x, cur.y, color);
			cur.x++;
		}
		cur.y++;
	}
}

void	draw_rect(t_env *env, t_vec2i pos, t_vec2i size, int color)
{
	t_vec2i cur;

	cur.y = pos.y;
	while (cur.y < pos.y + size.y)
	{
		cur.x = pos.x;
		while (cur.x < pos.x + size.x)
		{
			put_pixel_mlx_img(env->mlx_img, cur.x, cur.y, color);
			cur.x++;
		}
		cur.y++;
	}
}

void	draw_filler(t_env *env, t_vec2i map_offset, int tilesize)
{
	t_vec2i	cur;
	int		color;

	env->p1_score = 0;
	env->p2_score = 0;
	cur.y = 0;
	while (cur.y < env->map->height)
	{
		cur.x = 0;
		while (cur.x < env->map->width)
		{
			if (env->map->data[cur.y][cur.x] == '.')
				color = BG_C;
			else if (env->map->data[cur.y][cur.x] == env->p1 && (color = P1_C))
				env->p1_score++;
			else if (env->map->data[cur.y][cur.x] == env->p2 && (color = P2_C))
				env->p2_score++;
			draw_tile(env, ft_make_vec2i(cur.x * tilesize + map_offset.x,
				cur.y * tilesize + map_offset.y), tilesize, color);
			cur.x++;
		}
		cur.y++;
	}
}
