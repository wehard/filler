/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:31:42 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/06 14:42:29 by wkorande         ###   ########.fr       */
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
	debug_log("you are: %c\n", filler->player);
	debug_log("opponent is: %c\n", filler->opp);
}


