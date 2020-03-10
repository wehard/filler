/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:30:56 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/10 20:28:41 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <mlx.h>

t_env		*init_env(int width, int height, char *title)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		ft_panic("env malloc failed!");
	if (!(env->mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		ft_panic("env->mlx malloc failed!");
	env->width = width;
	env->height = height;
	env->mlx->mlx_ptr = mlx_init();
	env->mlx->win_ptr = mlx_new_window(env->mlx->mlx_ptr, width, height, title);
	env->mlx_img = create_mlx_image(env, width, height);
	return (env);
}

void		del_env_exit(t_env *env)
{
	mlx_destroy_image(env->mlx->mlx_ptr, env->mlx_img->img);
	mlx_destroy_window(env->mlx->mlx_ptr, env->mlx->win_ptr);
	free(env->mlx_img);
	free(env->mlx);
	free(env);
	exit(EXIT_SUCCESS);
}

int 		close_window(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
}

void		ft_panic(char *message)
{
	ft_printf("panic: %s\n", message);
	exit(EXIT_FAILURE);
}

t_mlx_img	*create_mlx_image(t_env *env, int width, int height)
{
	t_mlx_img *img;

	if (!(img = (t_mlx_img*)malloc(sizeof(t_mlx_img))))
		ft_panic("create_mlx_image failed!");
	img->width = width;
	img->height = height;
	if (!(img->img = mlx_new_image(env->mlx->mlx_ptr,
									img->width, img->height)))
		ft_panic("mlx_new_image failed!");
	if (!(img->d_addr = mlx_get_data_addr(img->img, &img->bpp,
										&img->size_line, &img->endian)))
		ft_panic("mlx_get_data_addr failed!");
	img->bpp /= 8;
	return (img);
}

void		put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c)
{
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	*(int*)(img->d_addr + (((y * img->width) + x) * img->bpp)) = c;
}
