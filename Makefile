# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/27 11:23:48 by rbohmert          #+#    #+#              #
#    Updated: 2016/05/26 23:43:31 by rbohmert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, fclean, clean, re

NAME = libft/libft.a

SRC = color.c fdf.c map.c put.c\

EXE = fdf

GCC = gcc -lmlx -framework Appkit -framework OpenGl -o $(EXE) -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@echo "\033[33mLibrary's compilation\033[0m"
	@make -C libft/
	@echo "\033[33mProject's compilation\033[0m"
	@$(GCC) $(SRC) $(NAME)
	@echo "\033[33mAll compilation done\033[0m" "\033[32m [ok] \033[32m"

clean:
	@echo "\033[33mLibrary's cleaning\033[0m"
	@make -C libft/ clean

fclean: clean
	@rm -rf $(EXE)
	@rm -rf $(NAME)
	@make -C libft/ fclean

re: fclean all
