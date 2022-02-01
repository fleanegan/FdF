# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/22 16:08:15 by tsiguenz          #+#    #+#              #
#   Updated: 2022/02/01 14:10:41 by                  ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME = fdf

# Paths

SRC_PATH = src/
LIB_PATH = lib/
OBJ_PATH = obj/

# Names

SRC_NAME =	main.c \
			draw_line.c \
			draw.c \
			view_operations.c \
			parsing.c \
			parsing_measure_map.c \
			manipulate_grid.c \
			debug.c \
			matrix.c \
			memory.c \
			key_handling.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

# Files

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

# Flags

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = $(LIB_PATH)libft/libft.a -I$(LIB_PATH)/libft

# Flags mlx for Linux and MacOS

UNAME=$(shell uname)
ifeq ($(UNAME), Linux)
	MLXFLAGS = -L$(LIB_PATH)mlx -lmlx -L/usr/lib -I$(LIB_PATH)mlx -lXext -lX11 -lm -lz
else
	MLXFLAGS = -L$(LIB_PATH)mlx -lmlx -framework OpenGL -framework AppKit -lm
endif

all: $(NAME)

PRE: 
	@echo 'pre exec'
	@make -C $(LIB_PATH)/libft/ --no-print-directory
	@make -C $(LIB_PATH)/mlx/ --no-print-directory


$(NAME): PRE $(OBJ)
	@echo "Build $(NAME)"
	@$(CC) -g $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(LIBFT) -g -I/usr/include -I$(LIB_PATH)/mlx -I$(SRC_PATH) -o $@ -c $<

clean:
	@make clean -C $(LIB_PATH)libft/ --no-print-directory
	@echo "Delete fdf/$(OBJ_PATH)"
	@rm -rf $(OBJ_PATH) db

fclean:	clean
	@make fclean -C $(LIB_PATH)libft/ --no-print-directory
	@echo "Delete fdf/$(NAME)"
	@rm -f $(NAME) db

db: $(SRC)
	$(CC) $(CFLAGS) -g $(SRC) $(LIBFT) $(MLX) -o $@
	gdb $@

re:	fclean all

.PHONY: all clean fclean re mlx libft db
