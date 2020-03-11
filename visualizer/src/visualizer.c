/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:49:25 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/11 12:54:57 by wkorande         ###   ########.fr       */
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

void		read_player(t_env *env, char *line)
{
	int num;
	num = ft_atoi(line + 10);
	if (num < 1 || num > 2)
		ft_panic("error: wrong player number!");
	if (num == 1)
	{
		env->p1 = 'O';
		env->p1_name = ft_strnew(ft_strlen(line));
		ft_strcpy(env->p1_name, ft_strchr(line, '['));
		ft_printf("p1: %s\n", env->p1_name);
	}
	else
	{
		env->p2 = 'X';
		env->p2_name = ft_strnew(ft_strlen(line));
		ft_strcpy(env->p2_name, ft_strchr(line, '['));
		ft_printf("p2: %s\n", env->p1_name);
	}

}

void read_map(t_map *map)
{
	char *line;
	int row;

	if (!map)
		ft_panic("map is null!");

	ft_get_next_line(0, &line); // Skip first because it just has unnecessary stuff
	row = 0;
	while (row < map->height && ft_get_next_line(0, &line))
	{
		if (line == NULL)
			continue;
		map->data[row] = ft_strncpy(map->data[row], line + 4, map->width);
		free(line);
		row++;
	}
}

void		read_output(t_env *env)
{
	char	*line;

	if (!env)
	{
		ft_printf("env is null!\n");
		return ;
	}

	while (ft_get_next_line(0, &line))
	{
		if (ft_strncmp(line, "$$$", 3) == 0)
			read_player(env, line);
		if (ft_strncmp(line, "Plateau", 7) == 0)
		{
			if (env->map == NULL)
			{
				char **split = ft_strsplit(line, ' ');
				env->map = create_map(ft_atoi(split[2]), ft_atoi(split[1]));
			}
			read_map(env->map);
		}
		if (ft_strncmp(line, "Piece", 5) == 0)
		{
			free(line);
			return ;
		}
	}
}

void	draw_tile(t_env *env, int x, int y, int size, int color)
{
	t_vec2i cur;

	cur.y = y+1;
	while (cur.y < y + size-1)
	{
		cur.x = x+1;
		while (cur.x < x + size-1)
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

void	render(t_env *env)
{
	t_vec2i	cur;
	t_vec2i map_offset;
	int tilesize;
	int p1_score;
	int p2_score;
	int tiles;

	tiles = env->map->width * env->map->height;
	p1_score = 0;
	p2_score = 0;

	mlx_clear_window(env->mlx->mlx_ptr, env->mlx->win_ptr);

	tilesize = ft_min(env->height / 120, env->height / env->map->height);
	map_offset.x = env->width / 2 - (env->map->width * tilesize) / 2;
	map_offset.y = env->height / 2 - (env->map->height * tilesize) / 2;

	cur.y = 0;
	while (cur.y < env->map->height)
	{
		cur.x = 0;
		while (cur.x < env->map->width)
		{
			int color;
			if (env->map->data[cur.y][cur.x] == '.')
				color = BG_COLOR;
			else if (env->map->data[cur.y][cur.x] == env->p1)
			{
				p1_score++;
				color = P1_COLOR;
			}
			else if (env->map->data[cur.y][cur.x] == env->p2)
			{
				p2_score++;
				color = P2_COLOR;
			}
			draw_tile(env, cur.x * tilesize + map_offset.x, cur.y * tilesize + map_offset.y, tilesize, color);
			cur.x++;
		}
		cur.y++;
	}
	draw_rect(env, ft_make_vec2i(map_offset.x + 1,map_offset.y - tilesize - 1), ft_make_vec2i(env->map->width*tilesize*((double)p1_score/(double)tiles),tilesize), P1_COLOR);
	draw_rect(env, ft_make_vec2i(map_offset.x + 1,map_offset.y + env->map->height * tilesize), ft_make_vec2i(env->map->width*tilesize*((double)p2_score/(double)tiles),tilesize), P2_COLOR);
	mlx_put_image_to_window(env->mlx->mlx_ptr, env->mlx->win_ptr, env->mlx_img->img, 0, 0);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, (env->width / 2) - (ft_strlen(env->p1_name)*10)/2, map_offset.y-30, P1_COLOR, env->p1_name);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, (env->width / 2) - (ft_strlen(env->p2_name)*10)/2, map_offset.y + env->map->height * tilesize+ tilesize, P2_COLOR, env->p2_name);
}

int	update(void *param)
{
	t_env *env;

	env = (t_env*)param;
	read_output(env);
	render(env);
	return (0);
}

int		key_press(int key, void *param)
{
	t_env *env;

	env = (t_env*)param;
	if (key == KEY_ESC )
		del_env_exit(env);
	return (0);
}

int		main(void)
{
	t_env	*env;

	env = init_env(1280, 720, "filler");

	mlx_hook(env->mlx->win_ptr, 2, (1L << 0), key_press, (void*)env);
	mlx_loop_hook(env->mlx->mlx_ptr, update, (void*)env);
	mlx_hook(env->mlx->win_ptr, 17, 0, close_window, (void*)env);
	mlx_loop(env->mlx->mlx_ptr);
	return (0);
}
