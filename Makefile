# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucho <lucho@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/23 00:39:56 by lucho             #+#    #+#              #
#    Updated: 2026/07/23 00:40:00 by lucho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =  src/main.c \
                src/engine/engine.c \
                src/engine/hooks.c \
                src/engine/raycasting.c \
                src/engine/render.c \
                src/engine/movement.c \
                src/engine/textures.c \
                src/engine/cleaning.c \
                src/parse/parse_arguments.c \
                src/parse/parse_textures.c \
                src/parse/parse_fc_colors1.c \
                src/parse/parse_fc_colors2.c \
                src/parse/parse_map.c \
                src/parse/parse_player.c \
                src/parse/flood_fill1.c \
                src/parse/flood_fill2.c \
                src/utils/utils1.c

OBJ_DIR = o_files
OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX42_DIR = MLX42
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a
MLX42_HEADERS = $(MLX42_DIR)/include

# Detect OS
UNAME_S := $(shell uname -s)

# Graphics linking flags (OS-specific). Darwin is macOS
ifeq ($(UNAME_S),Darwin)
    GRAPHICS_LIBS = $(MLX42_LIB) -Iinclude -lglfw -framework Cocoa -framework OpenGL -framework IOKit
else
    GRAPHICS_LIBS = $(MLX42_LIB) -Iinclude -ldl -lglfw -pthread -lm
endif

all: $(MLX42_LIB) $(NAME)

$(MLX42_LIB):
        cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build --log-level=ERROR
        cmake --build $(MLX42_DIR)/build --target mlx42 -- -j4

$(LIBFT_LIB):
        $(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX42_LIB)
        $(CC) $(CFLAGS) $(OBJS) $(GRAPHICS_LIBS) -L./$(LIBFT_DIR) -lft -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
        mkdir -p $(dir $@)
        $(CC) $(CFLAGS) -I$(LIBFT_DIR) -Iinclude -I$(MLX42_DIR)/include -c $< -o $@

$(OBJ_DIR):
        mkdir -p $(OBJ_DIR)

clean:
        $(RM) -r $(OBJ_DIR)
        $(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
        $(RM) $(NAME)
        $(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re sanitize

sanitize: CFLAGS += -fsanitize=address -g
sanitize: re