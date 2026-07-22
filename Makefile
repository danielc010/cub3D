# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucho <lucho@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/26 16:02:09 by dachin            #+#    #+#              #
#    Updated: 2026/07/22 23:20:45 by lucho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =	src/main.c \
		src/debug_map.c \
		src/engine/engine.c \
		src/engine/hooks.c \
		src/engine/raycasting.c \
		src/engine/render.c \
		src/engine/movement.c \
		src/engine/textures.c \
		src/engine/cleaning.c


OBJ_DIR = o_files
OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_DIR = MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
LDLIBS = -ldl -lglfw -pthread -lm

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build --log-level=ERROR
	cmake --build $(MLX_DIR)/build --target mlx42 -- -j4

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) -L./$(LIBFT_DIR) -lft -L./$(MLX_DIR)/build -lmlx42 $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -Iinclude -I$(MLX_DIR)/include -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re