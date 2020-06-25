# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2020/06/25 19:14:39 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wkorande.filler

CFLAGS = -Wall -Wextra -Werror

SRC = main.c\
	area.c\
	debug.c\
	map.c\
	heat_map.c\
	piece.c\
	player.c\
	search.c\
	strategy_fallback.c\
	strategy_grid.c\
	strategy_heat.c\
	strategy_circ_search.c

SRCDIR = src

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OBJS = $(SRC:.c=.o)

INCL = include

LIBFT=libft

FLAGS= -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C libft
	gcc $(FLAGS) -DBUFFSIZE1 -o $(NAME) -I$(INCL) -I $(LIBFT)/includes $(SRCS) -L$(LIBFT) -lft -lm -O2

debug:
	make -C libft
	gcc -g $(FLAGS) -DBUFFSIZE1 -o $(NAME) -I$(INCL) -I $(LIBFT)/includes $(SRCS) -L$(LIBFT) -lft -lm

clean:
	@printf "Removing objects\n"
	@rm -f $(OBJS)

fclean : clean
	@printf "Removing $(NAME)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
