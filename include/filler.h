/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:18:45 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/10 13:44:46 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "vector.h"

# define STDIN 0
# define ASTERISK '*'
# define P1 'O'
# define P2 'X'

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
	t_vec2i		min_offset;
	t_vec2i		max_offset;
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
	char		player;
	int			player_start_set;
	t_vec2		player_start;
	char		opp;
	t_vec2		opp_start;
	int			opp_start_set;
	t_map		*map;
	int			spider_radius;
	int			spider_angle;
	int			spider_spread;
	int			spider_legs;
	int			opp_tl;
	int			opp_tr;
	int			opp_bl;
	int			opp_br;
}				t_filler;

typedef struct	s_search_info
{
	t_vec2		pos;
	int			beg_rad;
	int			end_rad;
	int			step_angle;
	int			size;
}				t_search_info;

void			ft_panic(char *error);

t_map			*create_map(int width, int height);
char 			**make_area(int width, int height);
void 			populate_area(char **area, int width, int height, int line_offset);

void			read_map_state(t_map *map);
t_piece 		*read_piece(int width, int height);
int				test_piece(t_filler *filler, t_piece piece, t_vec2i pos);

void			read_player_info(t_filler *filler, int n);
t_vec2			get_player_start(char player, t_filler *filler);

t_vec2i			calc_piece_offset(t_piece piece);
t_vec2i			get_position(t_filler *filler, t_piece piece);

t_vec2i			strategy_grid(t_filler *filler, t_piece piece);
t_vec2i			strategy_spider(t_filler *filler, t_piece piece);
t_vec2i			strategy_fallback(t_filler *filler, t_piece piece);

int				search_radius(t_filler *filler, t_piece piece, t_search_info info, t_vec2 *valid_pos);
int				search_area(t_filler *filler, t_piece piece, t_search_info info, t_vec2 *valid_pos);
#endif
