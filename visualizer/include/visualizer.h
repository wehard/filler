/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:50:07 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/10 20:29:06 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "vector.h"
# include "time.h"
# include "matrix.h"
# include "color.h"

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
	char		p2;
}				t_env;

t_env			*init_env(int width, int height, char *title);
void			del_env_exit(t_env *env);
int				close_window(void *param);
t_mlx_img		*create_mlx_image(t_env *env, int width, int height);
void			put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c);

t_map 			*create_map(int width, int height);

void			ft_panic(char *message);

#endif
