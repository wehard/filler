/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:18:45 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/05 18:08:19 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

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

void	ft_panic(char *error);
void read_player_info(t_filler *filler, char *line);

#endif
