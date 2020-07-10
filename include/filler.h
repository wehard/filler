/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:18:45 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/10 15:38:22 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "vector.h"

# define STDIN 0
# define ASTERISK '*'
# define P1 'O'
# define P2 'X'
# define DIR_TOPLEFT 0
# define DIR_TOPRIGHT 1
# define DIR_BOTTOMLEFT 2
# define DIR_BOTTOMRIGHT 3


typedef struct	s_map
{
	int			width;
	int			height;
	char		**data;
}				t_map;

typedef struct	s_heat_map
{
	int			width;
	int			height;
	int			*data;
}				t_heat_map;

typedef struct	s_piece
{
	int			width;
	int			height;
	t_vec2i		min_offset;
	t_vec2i		max_offset;
	char		**data;
	int			num_overlap;
}				t_piece;

typedef struct	s_player
{
	int			x;
	int			y;
	char		c;
}				t_player;

typedef struct	s_filler
{
	char		pl;
	int			player_start_set;
	t_vec2i		player_start;
	char		opp;
	t_vec2i		opp_start;
	int			opp_start_set;
	t_map		*map;
	t_heat_map	*heat_map;
	int			spider_radius;
	int			spider_angle;
	int			spider_spread;
	int			spider_legs;
	int			opp_tl;
	int			opp_tr;
	int			opp_bl;
	int			opp_br;
	int			turn;
	int			grid_size;
	t_vec2i		player_last;
	t_vec2i		opp_last;
}				t_filler;

typedef struct	s_search_info
{
	t_vec2		pos;
	int			beg_rad;
	int			end_rad;
	int			step_angle;
	int			size;
	int			start_angle;
	int			end_angle;
}				t_search_info;

typedef t_vec2i	(*strategy_func)(t_filler *f, t_piece *p);

void			ft_panic(char *error);

t_map			*create_map(char *line);
char 			**make_area(int width, int height);
void 			populate_area(char **area, int width, int height, int line_offset);

t_heat_map		*create_heat_map(int width, int height);
void			update_heat_map(t_filler *filler);
int				get_score(t_filler *filler, t_vec2i pos);
void			read_map_state(t_map *map);
t_piece 		*read_piece(char *line);
int				test_piece(t_filler *filler, t_piece *piece, t_vec2i pos);

void			read_player_info(t_filler *filler, int n);
t_vec2i			get_player_start(char player, t_filler *filler);
t_vec2i			get_player_last_pos(char player, t_filler *filler);

void			calc_piece_offset(t_piece *piece);

t_vec2i			strategy_grid(t_filler *filler, t_piece *piece);
t_vec2i			strategy_fallback(t_filler *filler, t_piece *piece);
t_vec2i			strategy_heat(t_filler *filler, t_piece *piece);
t_vec2i			strategy_circ_search(t_filler *filler, t_piece *piece);
t_vec2i			strategy_fallback_dir(t_filler *filler, t_piece *piece, int dir);

int				search_radius(t_filler *filler, t_piece *piece, t_search_info info, t_vec2 *valid_pos);
int				search_area(t_filler *filler, t_piece *piece, t_search_info info, t_vec2 *valid_pos);
t_vec2 			search_opp(t_filler *filler, t_vec2 pos);
int				check_opp_fill(t_filler *filler, int res);
int				get_distance_to_opp(t_filler *filler, t_vec2i pos);

#endif
