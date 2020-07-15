/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:56:44 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/15 17:51:47 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "ft_get_next_line.h"
#include "ft_printf.h"
#include "vector.h"
#include "debug.h"
#include <unistd.h>
#include <fcntl.h>

void		ft_panic(char *error)
{
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

t_filler	*init_filler(void)
{
	t_filler *filler;

	if (!(filler = (t_filler*)malloc(sizeof(t_filler))))
	{
		debug_log("init_filler: malloc error!\n");
		return (NULL);
	}
	filler->player_start_set = 0;
	filler->player_start = ft_make_vec2i(-1, -1);
	filler->opp_start_set = 0;
	filler->opp_start = ft_make_vec2i(-1, -1);
	filler->spider_radius = 0;
	filler->spider_angle = 0;
	filler->spider_spread = 90;
	filler->spider_legs = 3;
	filler->map = NULL;
	filler->heat_map = NULL;
	filler->turn = 0;
	filler->grid_size = 20;
	return (filler);
}

void		init_map(t_filler *filler, char *line)
{
	filler->map = create_map(line);
	filler->heat_map = create_heat_map(filler->map->width, filler->map->height);
}

void		output_pos(t_filler *filler, t_piece *piece, t_strategy_func func)
{
	t_vec2i pos;

	pos = func(filler, piece);
	filler->player_last = pos;
	pos.x -= piece->min_offset.x;
	pos.y -= piece->min_offset.y;
	ft_printf("%d %d\n", pos.y, pos.x);
}

int			main(void)
{
	t_piece		*piece;
	t_filler	*filler;
	char		*line;

	filler = init_filler();
	piece = NULL;
	while (ft_get_next_line(STDIN, &line))
	{
		if (ft_strncmp(line, "$$$", 3) == 0)
			read_player_info(filler, ft_atoi(line + 10));
		else if (ft_strncmp(line, "Plateau", 7) == 0)
		{
			if (filler->map == NULL)
				init_map(filler, line);
			read_map_state(filler->map);
		}
		else if (ft_strncmp(line, "Piece", 5) == 0)
		{
			if ((piece = read_piece(line)) && ++filler->turn)
				output_pos(filler, piece, strategy_heat);
		}
		free(line);
	}
	return (0);
}
