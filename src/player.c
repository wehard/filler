/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:31:42 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/05 19:15:58 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "debug.h"

void read_player_info(t_filler *filler, char *line)
{
	int player_number;
	player_number = ft_atoi(ft_strchr(line, 'p') + 1);
	if (player_number < 1 || player_number > 2)
		ft_panic("error: wrong player number!");
	filler->me.c = player_number == 1 ? 'O' : 'X';
	//debug_log("we are: %c\n", filler->me.c);
}


