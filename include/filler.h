/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:18:45 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/05 23:13:20 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "vector.h"

# define STDIN 0
# define ASTERISK '*'

typedef struct	s_map
{
	int			width;
	int			height;
	char		**data;
}				t_map;

typedef struct	s_piece
{
	int			width;
	int			height;
	char		**data;
}				t_piece;

typedef struct	s_player
{
	int			x;
	int			y;
	char		c;
}				t_player;

typedef struct	s_filler
{
	t_player	me;
	t_map		*map;
}				t_filler;

void			ft_panic(char *error);
void 			read_player_info(t_filler *filler, int n);
t_piece 		*read_piece(int width, int height);
char 			**make_area(int width, int height);
void 			populate_area(char **area, int width, int height, int line_offset);

t_map			*create_map(int width, int height);
void			read_map_state(t_map *map);
t_vec2i 		get_decent_position(t_map map, t_piece piece);
t_vec2i 		calc_top_left_corner(t_piece piece);


#endif
