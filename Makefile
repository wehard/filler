# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2020/07/10 16:37:05 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wkorande.filler

SRC = main.c\
	area.c\
	debug.c\
	map.c\
	piece.c\
	piece_offset.c\
	player.c\
	search.c\
	strategy_fallback.c\
	strategy_grid.c\
	strategy_heat.c

SRCDIR = src

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OBJS = $(SRC:.c=.o)

INCL = include

LIBFT=libft

CFLAGS= -Wall -Wextra -Werror

CC=clang

all: $(NAME)

$(NAME): libft
	$(CC) $(CFLAGS) -DBUFFSIZE1 -o $(NAME) -I$(INCL) -I $(LIBFT)/includes $(SRCS) -L$(LIBFT) -lft -lm -O2

debug: libft
	make -C libft
	$(CC) -g $(CFLAGS) -DBUFFSIZE1 -o $(NAME) -I$(INCL) -I $(LIBFT)/includes $(SRCS) -L$(LIBFT) -lft -lm

libft:
	make -C libft

clean:
	@printf "Removing objects\n"
	@rm -f $(OBJS)

fclean : clean
	@printf "Removing $(NAME)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
