# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2020/03/10 20:43:07 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visual

CFLAGS = -Wall -Wextra -Werror

SRCS = visualizer.c\
		env.c\
		map.c

SRCDIR = src

SRC = $(addprefix $(SRCDIR)/, $(SRCS))

OUT = $(SRCS:.c=.o)

INCL = include

LIBFT= ../libft

FLAGS= #-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	gcc $(FLAGS) -o $(NAME) -I$(INCL) -I $(LIBFT)/includes $(SRC) -L$(LIBFT) -lft -lmlx -framework OpenGL -framework AppKit

linux:
	make -C $(LIBFT)
	gcc $(FLAGS) -o $(NAME) -I$(INCL) -I $(LIBFT)/includes $(SRC) -L$(LIBFT) -lft -lmlx -lXext -lX11 -lm

clean:
	make clean -C $(LIBFT)
	@echo "Removing object files ..."
	@rm -f $(OBJ)

fclean : clean
	make fclean -C $(LIBFT)
	@echo "Removing $(NAME) ..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re