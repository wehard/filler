/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:47:31 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/18 22:21:39 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "libft.h"
#include "ft_get_next_line.h"
#include "ft_printf.h"

void	read_player(t_env *env, char *line)
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
		ft_printf("p2: %s\n", env->p2_name);
	}
}

void	read_map(t_map *map)
{
	char	*line;
	int		row;

	if (!map)
		ft_panic("map is null!");
	ft_get_next_line(0, &line);
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

void	read_output(t_env *env)
{
	char	**split;
	char	*line;

	if (!env)
	{
		ft_printf("env is null!\n");
		return ;
	}
	while (ft_get_next_line(0, &line) == 1)
	{
		if (ft_strncmp(line, "$$$", 3) == 0)
			read_player(env, line);
		if (ft_strncmp(line, "Plateau", 7) == 0)
		{
			if (env->map == NULL)
			{
				split = ft_strsplit(line, ' ');
				env->map = create_map(ft_atoi(split[2]), ft_atoi(split[1]));
			}
			read_map(env->map);
		}
		if (ft_strncmp(line, "Piece", 5) == 0)
		{
			free(line);
			return ;
		}
		free(line);
	}
}
