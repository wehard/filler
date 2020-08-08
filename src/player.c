/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:31:42 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/08 08:53:28 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "debug.h"

void	read_player_info(t_filler *filler, int n)
{
	int player_number;

	player_number = n;
	if (player_number < 1 || player_number > 2)
		ft_panic("error: wrong player number!");
	filler->pl = player_number == 1 ? 'O' : 'X';
	filler->opp = player_number == 1 ? 'X' : 'O';
}

t_vec2i	get_player_last_pos(char player, t_filler *filler)
{
	t_vec2i cur;

	cur.y = 0;
	while (cur.y < filler->map->height)
	{
		cur.x = 0;
		while (cur.x < filler->map->width)
		{
			if (filler->map->data[cur.y][cur.x] == player)
				return (cur);
			cur.x++;
		}
		cur.y++;
	}
	return (get_player_start(player, filler));
}

t_vec2i	get_player_start(char player, t_filler *filler)
{
	if (player == filler->pl && filler->player_start_set)
		return (filler->player_start);
	else
		return (get_player_last_pos(player, filler));
	if (player == filler->opp && filler->opp_start_set)
		return (filler->opp_start);
	else
		return (get_player_last_pos(player, filler));
}
