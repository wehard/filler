/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:56:44 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/05 19:32:25 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "ft_get_next_line.h"
#include "ft_printf.h"
#include "vector.h"
#include "debug.h"

#define FD 0

void	ft_panic(char *error)
{
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

char **make_area(int width, int height)
{
	char **area;
	int y;

	area = (char**)malloc(sizeof(char*) * height);
	y = 0;
	while (y < height)
	{
		area[y] = (char*)malloc(sizeof(char) * width);
		ft_bzero(area[y], width);
		y++;
	}
	return (area);
}

void populate_area(char **area, int width, int height, int line_offset)
{
	char *line;
	int row;

	row = 0;
	while (row < height && ft_get_next_line(FD, &line))
	{
		debug_log(line);
		if (line == NULL)
			continue;
		area[row] = ft_strncpy(area[row], line + line_offset, width);
		free(line);
		row++;
	}
}

t_map *create_map(int width, int height) {
	t_map *map;

	map = (t_map*)malloc(sizeof(t_map));
	map->width = width;
	map->height = height;
	map->data = make_area(width, height);
	//debug_log("created map: %d %d\n", height, width);
	return (map);
}

void read_map_state(t_map *map)
{
	char *line;
	int y;

	y = 0;
	ft_get_next_line(FD, &line); // Skip first because it just has unnecessary stuff
	populate_area(map->data, map->width, map->height, 4);
	//print_area(map->data, map->width, map->height);
}

t_piece *read_piece(int width, int height)
{
	t_piece *piece;

	piece = (t_piece*)malloc(sizeof(t_piece));
	piece->height = height;
	piece->width =  width;
	if (piece->width < 1 || piece->height < 1)
	{
		ft_printf("error: bad piece dimensions!\n");
		return (NULL);
	}
	piece->data = make_area(piece->width, piece->height);
	populate_area(piece->data, piece->width, piece->height, 0);
	//print_area(piece->data, piece->width, piece->height);
	return (piece);
}


int	main(void)
{
	t_piece *piece;
	t_filler *filler;

	debug_log("----------\n");
	filler = (t_filler*)malloc(sizeof(t_filler));
	filler->map = NULL;
	piece = NULL;

	char *line;
	while (ft_get_next_line(FD, &line))
	{
		debug_log(line);
		if (ft_strncmp(line, "$$$", 3) == 0)
			read_player_info(filler, line);
		if (ft_strncmp(line, "Plateau", 7) == 0)
		{
			if (filler->map == NULL)
			{
				char **split = ft_strsplit(line, ' ');
				filler->map = create_map(ft_atoi(split[2]), ft_atoi(split[1]));
			}
			read_map_state(filler->map);
		}
		if (ft_strncmp(line, "Piece", 5) == 0)
		{
			char **split = ft_strsplit(line, ' ');
			piece = read_piece(ft_atoi(split[2]), ft_atoi(split[1]));
			debug_log("8 2\n");
		}
		free(line);
	}
	return (0);
}
