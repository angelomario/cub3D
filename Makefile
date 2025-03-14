# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 17:25:17 by aquissan          #+#    #+#              #
#    Updated: 2025/03/14 12:11:50 by aquissan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=cub3D

FLAGS= -Wall -Wextra -Werror -g
COMPILE= cc

# DIRS
INC_D = includes
LIBFTPATH = libft
MLXPATH = minilibx-linux
SRC_D=sources
OBJ_D=objects

RM=rm -rf 
Mk=mkdir -p 

FILES= main.c get_next_line.c get_next_line_utils.c check_map.c freeze.c gets.c\
		utils_check.c utils.c check_walls.c utils2.c render.c controls.c dda.c\
		extra.c draw.c
SRC=$(addprefix $(SRC_D)/, $(FILES))
OBJ=$(addprefix $(OBJ_D)/, $(FILES:.c=.o))

all: MLX LIBFT $(NAME)

MLX:
	make -C $(MLXPATH)
LIBFT:
	make -C $(LIBFTPATH)

$(NAME): $(OBJ)
	$(COMPILE) $(FLAGS)  -Iincludes -Imimilibx-linux $(OBJ) -L./$(MLXPATH) -lmlx -L./$(LIBFTPATH) -lft -I$(MLXPATH) -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_D)/%.o:$(SRC_D)/%.c
	@$(Mk) $(OBJ_D)
	$(COMPILE) $(FLAGS) -c $< -o $@ 
clean: 
	make clean -C $(LIBFTPATH)
	make clean -C $(MLXPATH)
	$(RM) $(OBJ)
	$(RM) $(OBJ_D)

fclean: clean
	make fclean -C $(LIBFTPATH)
	# make fclean -C $(MLXPATH)
	$(RM) $(NAME)

re: fclean all

run: MLX LIBFT
	$(RM) $(OBJ)
	$(RM) $(OBJ_D)
	$(RM) $(NAME)
	make
	clear
	./$(NAME) "test.cub"

leak: MLX LIBFT
	$(RM) $(OBJ)
	$(RM) $(OBJ_D)
	$(RM) $(NAME)
	make
	clear
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(NAME) "test.cub"

push: fclean
	clear
	git status
	git add .
	git status
	git commit -m "done"
	git push

norm:
	norminette $(LIBFTPATH) $(SRC_D) $(INC_D)

.PHONY: all re clean fclean

