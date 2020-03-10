/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:49:25 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/10 20:36:39 by wkorande         ###   ########.fr       */
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

void		read_player(t_env *env, char *line)
{
	int num;
	num = ft_atoi(line + 10);
	if (num < 1 || num > 2)
		ft_panic("error: wrong player number!");
	env->p1 = num == 1 ? 'O' : 'X';
	env->p2 = num == 1 ? 'X' : 'O';
}

void read_map(t_map *map)
{
	char *line;
	int row;

	ft_get_next_line(0, &line); // Skip first because it just has unnecessary stuff
	row = 0;
	while (row < map->height && ft_get_next_line(0, &line))
	{
		if (line == NULL)
			continue;
		map->data[row] = ft_strncpy(map->data[row], line, map->width);
		free(line);
		row++;
	}
}

void		read_output(t_env *env)
{
	char	*line;

	while (ft_get_next_line(0, &line) == 1)
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

int	update(void *param)
{
	t_env *env;

	env = (t_env*)param;
	read_output(env);
	ft_printf("env w%d h%d\n", env->width, env->height);
	return (0);
}

void	render(t_env *env)
{
	t_vec2i	cur;

	cur.y = 0;
	while (cur.y < env->height)
	{
		cur.x = 0;
		while (cur.x < env->width)
		{

			cur.x++;
		}
		cur.y++;
	}
}

int		main(void)
{
	t_env	*env;

	env = init_env(1280, 720, "fillit");

	render(env);
	//mlx_hook(env->mlx->win_ptr, 2, (1L << 0), key_press, (void*)env);
	//mlx_expose_hook(env->mlx->win_ptr, update, (void*)env);
	//mlx_hook(env->mlx->win_ptr, 4, (1L << 2), mouse_press, (void*)env);
	mlx_loop_hook(env->mlx, update, (void*)env);
	mlx_hook(env->mlx->win_ptr, 17, 0, close_window, (void*)env);
	mlx_loop(env->mlx->mlx_ptr);
	return (0);
}
