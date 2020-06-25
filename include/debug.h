/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:06:01 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/25 20:16:50 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

#include <stdio.h>

#define DEBUG_LOG(X, Y) fprintf (g_file, #X ": Time:%s, File:%s(%d) " #Y  "\n", __TIMESTAMP__, __FILE__, __LINE__)

FILE	*g_file;

void	init_logger(char *filename, char *mode);
void	close_logger(void);
void	debug_log_fput(const char *str);
void	debug_log(const char *format, ...);
void	debug_log_char(const char c);
void	print_area(char **area, int width, int height);
void	print_heat_map(int *map, int width, int height);

#endif
