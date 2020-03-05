/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:06:01 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/05 22:13:22 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

void	debug_log(const char *format, ...);
void	debug_log2(const char *format,...);
void	print_area(char **area, int width, int height);

#endif
