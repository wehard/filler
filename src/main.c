/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:56:44 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/06 18:34:23 by wkorande         ###   ########.fr       */
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

void	ft_panic(char *error)
{
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

int	main(void)
{
	t_piece *piece;
	t_filler *filler;

	filler = (t_filler*)malloc(sizeof(t_filler));
	filler->map = NULL;
	piece = NULL;

	char *line;
	init_logger("debug.log", "w");
	while (ft_get_next_line(STDIN, &line))
	{
		//debug_log(line);
		if (ft_strncmp(line, "$$$", 3) == 0)
		{
			read_player_info(filler, ft_atoi(line + 10));
		}
		else if (ft_strncmp(line, "Plateau", 7) == 0)
		{
			if (filler->map == NULL)
			{
				char **split = ft_strsplit(line, ' ');
				filler->map = create_map(ft_atoi(split[2]), ft_atoi(split[1]));
			}
			read_map_state(filler->map);
		}
		else if (ft_strncmp(line, "Piece", 5) == 0)
		{
			char **split = ft_strsplit(line, ' ');
			piece = read_piece(ft_atoi(split[2]), ft_atoi(split[1]));
			if (piece != NULL)
			{
				t_vec2i p;
				p = get_decent_position(*filler, *filler->map, *piece);
				debug_log("piece pos: r%d c%d\n", p.y, p.x);
				ft_printf("%d %d\n", p.y, p.x);
			}
			else
				break ;
		}
		free(line);
	}
	close_logger();
	return (0);
}
