# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2020/08/06 20:42:06 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visual

CFLAGS = -Wall -Wextra -Werror

SRCS = visualizer.c\
		env.c\
		map.c\
		draw.c\
		read.c

SRCDIR = src

SRC = $(addprefix $(SRCDIR)/, $(SRCS))

OUT = $(SRCS:.c=.o)

INCL = include

LIBFT= ../libft

FLAGS= -Wall -Wextra -Werror

CC=clang

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) -I$(INCL) -I $(LIBFT)/includes $(SRC) -L$(LIBFT) -lft -lmlx -framework OpenGL -framework AppKit

linux:
	make -C $(LIBFT)
	$(CC) -g $(FLAGS) -o $(NAME) -I$(INCL) -I $(LIBFT)/includes $(SRC) -L$(LIBFT) -lft -lmlx -lXext -lX11 -lm

clean:
	@echo "Removing object files ..."
	@rm -f $(OBJ)

fclean : clean
	@echo "Removing $(NAME) ..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
