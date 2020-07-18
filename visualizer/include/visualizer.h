/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:50:07 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/18 22:10:07 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "vector.h"
# include "time.h"
# include "matrix.h"
# include "color.h"

# define P1_C 0xEA9A21
# define P2_C 0x3B74C3
# define BG_C 0x282828

typedef struct	s_mlx_img
{
	void		*img;
	char		*d_addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_mlx_img;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
}				t_mlx;

typedef struct	s_map
{
	int			width;
	int			height;
	char		**data;
}				t_map;

typedef struct	s_env
{
	t_mlx		*mlx;
	t_mlx_img	*mlx_img;
	int			width;
	int			height;
	t_map		*map;
	char		p1;
	char		*p1_name;
	char		p2;
	char		*p2_name;
	int			p1_score;
	int			p2_score;
}				t_env;

t_env			*init_env(int width, int height, char *title);
void			del_env_exit(t_env *env);
int				close_window(void *param);
t_mlx_img		*create_mlx_image(t_env *env, int width, int height);
void			put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c);

t_map 			*create_map(int width, int height);

void			read_player(t_env *env, char *line);
void			read_map(t_map *map);
void			read_output(t_env *env);

void			draw_filler(t_env *env, t_vec2i map_offset, int tilesize);
void			draw_tile(t_env *env, t_vec2i pos, int size, int color);
void			draw_rect(t_env *env, t_vec2i pos, t_vec2i size, int color);

void			ft_panic(char *message);

#endif
