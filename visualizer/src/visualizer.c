/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:49:25 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/06 17:46:48 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "libft.h"
#include "ft_get_next_line.h"
#include "ft_printf.h"
#include <stdio.h>
#include <mlx.h>
#include "keys.h"
#include "vector.h"
#include <unistd.h>
#include <errno.h>

void	ft_panic(char *message)
{
	ft_printf("panic: %s\n", message);
	exit(EXIT_FAILURE);
}

void	render(t_env *env)
{
	t_vec2i	map_offset;
	int		tilesize;
	int		tiles;

	tiles = env->map->width * env->map->height;
	tilesize = ft_min(env->height / 120, env->height / env->map->height);
	map_offset.x = env->width / 2 - (env->map->width * tilesize) / 2;
	map_offset.y = env->height / 2 - (env->map->height * tilesize) / 2;
	draw_filler(env, map_offset, tilesize);
	draw_rect(env, ft_make_vec2i(map_offset.x + 1, map_offset.y - tilesize - 1),
		ft_make_vec2i(env->map->width * tilesize * ((double)env->p1_score /
		(double)tiles), tilesize), P1_C);
	draw_rect(env, ft_make_vec2i(map_offset.x + 1,
		map_offset.y + env->map->height * tilesize + 1),
		ft_make_vec2i(env->map->width * tilesize * ((double)env->p2_score /
		(double)tiles), tilesize), P2_C);
	mlx_put_image_to_window(env->mlx->mlx_ptr, env->mlx->win_ptr,
		env->mlx_img->img, 0, 0);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, (env->width / 2) -
		(ft_strlen(env->p1_name) * 10) / 2, map_offset.y - 30, P1_C,
		env->p1_name);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, (env->width / 2) -
		(ft_strlen(env->p2_name) * 10) / 2, map_offset.y + env->map->height *
		tilesize + tilesize, P2_C, env->p2_name);
}

int		update(void *param)
{
	t_env *env;

	env = (t_env*)param;
	read_output(env);
	render(env);
	return (1);
}

int		key_press(int key, void *param)
{
	t_env *env;

	env = (t_env*)param;
	if (key == KEY_ESC)
		del_env_exit(env);
	return (0);
}

int		main(void)
{
	t_env	*env;

	if (!(env = init_env(1280, 720, "filler")))
		ft_panic("failed to init visualizer!");
	mlx_hook(env->mlx->win_ptr, 2, (1L << 0), key_press, (void*)env);
	mlx_hook(env->mlx->win_ptr, 17, (1L << 17), close_window, (void*)env);
	mlx_loop_hook(env->mlx->mlx_ptr, update, (void*)env);
	mlx_loop(env->mlx->mlx_ptr);
	return (0);
}
