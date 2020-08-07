/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:02:06 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/07 15:08:12 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

t_filler	*init_filler(void)
{
	t_filler *filler;

	if (!(filler = (t_filler*)malloc(sizeof(t_filler))))
	{
		ft_putendl_fd("init_filler: malloc error!", 2);
		return (NULL);
	}
	filler->player_start_set = 0;
	filler->player_start = ft_make_vec2i(-1, -1);
	filler->opp_start_set = 0;
	filler->opp_start = ft_make_vec2i(-1, -1);
	filler->map = NULL;
	filler->heat_map = NULL;
	filler->turn = 0;
	filler->grid_size = 20;
	return (filler);
}

void		destroy_filler(t_filler *filler)
{
	free(filler->heat_map->data);
	free(filler->heat_map);
	destroy_area(filler->map->data, filler->map->height);
	free(filler->map);
	free(filler);
}
