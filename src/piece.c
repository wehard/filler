/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:32:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/14 20:40:03 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "vector.h"
#include "debug.h"
#include <stdlib.h>

t_piece	*read_piece(char *line)
{
	t_piece	*piece;
	char	**split;

	if (!(piece = (t_piece*)malloc(sizeof(t_piece))))
		ft_panic("read_piece: malloc failed!");
	split = ft_strsplit(line, ' ');
	piece->height = ft_atoi(split[1]);
	piece->width = ft_atoi(split[2]);
	piece->num_overlap = 0;
	if (piece->width < 1 || piece->height < 1)
		ft_panic("error: bad piece dimensions!");
	piece->data = make_area(piece->width, piece->height);
	populate_area(piece->data, piece->width, piece->height, 0);
	calc_piece_offset(piece);
	piece->best_score = INT32_MAX;
	return (piece);
}

int		test_piece(t_filler *f, t_piece *pc, t_vec2i pos)
{
	t_vec2i	m;
	t_vec2i	p;

	pc->num_overlap = 0;
	p.y = pc->min_offset.y;
	m.y = pos.y;
	while (p.y < pc->height - pc->max_offset.y)
	{
		p.x = pc->min_offset.x;
		m.x = pos.x;
		while (p.x < pc->width - pc->max_offset.x)
		{
			if (pc->data[p.y][p.x] == '*' && f->map->data[m.y][m.x] == f->opp)
				return (0);
			if (pc->data[p.y][p.x] == '*' && f->map->data[m.y][m.x] == f->pl)
				pc->num_overlap++;
			if (pc->num_overlap > 1)
				return (0);
			p.x++;
			m.x++;
		}
		p.y++;
		m.y++;
	}
	return (pc->num_overlap == 1);
}
