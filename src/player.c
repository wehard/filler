/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:31:42 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/30 18:04:55 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "debug.h"

void read_player_info(t_filler *filler, int n)
{
	int player_number;
	player_number = n;
	if (player_number < 1 || player_number > 2)
		ft_panic("error: wrong player number!");
	filler->player = player_number == 1 ? 'O' : 'X';
	filler->opp = player_number == 1 ? 'X' : 'O';
	// debug_log("you are: %c\n", filler->player);
	// debug_log("opponent is: %c\n", filler->opp);
}

t_vec2 get_player_start(char player, t_filler *filler)
{
	t_vec2i cur;

	if (player == filler->player && filler->player_start_set)
		return (filler->player_start);
	if (player == filler->opp && filler->opp_start_set)
		return (filler->opp_start);
	cur.x = 0;
	cur.y = 0;
	while (cur.y < filler->map->height)
	{
		cur.x = 0;
		while (cur.x < filler->map->width)
		{
			if (filler->map->data[cur.y][cur.x] == player)
			{
				debug_log("player %c start: r%d c%d\n", player, cur.y, cur.x);
				if (player == filler->player)
				{
					filler->player_start_set = 1;
					filler->player_start = ft_make_vec2(cur.x, cur.y);
					return (filler->player_start);
				}
				else if (player == filler->opp)
				{
					filler->opp_start_set = 1;
					filler->opp_start = ft_make_vec2(cur.x, cur.y);
					return (filler->opp_start);
				}
			}
			cur.x++;
		}
		cur.y++;
	}
	return (ft_make_vec2(cur.x, cur.y));
}
