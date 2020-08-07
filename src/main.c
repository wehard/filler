/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:56:44 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/07 15:11:39 by wkorande         ###   ########.fr       */
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

void		output_pos(t_filler *filler, t_piece *piece, t_strategy_func func)
{
	t_vec2i pos;

	pos = func(filler, piece);
	filler->player_last = pos;
	pos.x -= piece->min_offset.x;
	pos.y -= piece->min_offset.y;
	destroy_piece(piece);
	ft_printf("%d %d\n", pos.y, pos.x);
}

int			main(void)
{
	t_piece		*piece;
	t_filler	*filler;
	char		*line;

	if (!(filler = init_filler()))
		ft_panic("failed to init filler!");
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
	destroy_filler(filler);
	return (0);
}
