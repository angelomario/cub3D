#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 17:25:17 by aquissan          #+#    #+#              #
#    Updated: 2025/02/11 10:25:25 by aquissan         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME=cub3D

FLAGS=-Wall -Wextra -Werror -g
COMPILE= cc

# DIRS
SRC_D=sources
OBJ_D=objects

RM=rm -rf 
Mk=mkdir -p 

FILES= main.c get_next_line.c get_next_line_utils.c check_map.c freeze.c
SRC=$(addprefix $(SRC_D)/, $(FILES))
OBJ=$(addprefix $(OBJ_D)/, $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILE) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_D)/%.o:$(SRC_D)/%.c
	@$(Mk) $(OBJ_D)
	$(COMPILE) $(FLAGS) -c $< -o $@ 

clean: 
	$(RM) $(OBJ)
	$(RM) $(OBJ_D)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	clear
	valgrind --leak-check=full -s ./$(NAME) "test.txt"

push: fclean
	clear
	git status
	git add .
	git status
	git commit -m "done"
	git push

.PHONY: all re clean fclean

