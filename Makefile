# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dachin <dachin@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2026/06/26 16:02:09 by dachin        #+#    #+#                  #
#    Updated: 2026/07/12 22:41:04 by dachin        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = 	src/main.c \
		src/parse/parse_arguments.c \
		src/parse/parse_textures.c \
		src/parse/parse_fc_colors1.c \
		src/parse/parse_fc_colors2.c \
		src/parse/parse_map.c \
		src/parse/parse_player.c \
		src/parse/flood_fill1.c \
		src/utils/utils1.c \

OBJ_DIR = o_files
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# MLX42 paths and libraries
MLX42_DIR = ../MLX42
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

all: $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

# Check if MLX42 library exists, if not provide helpful error
$(MLX42_LIB):
	@if [ ! -f $(MLX42_LIB) ]; then \
		echo "Error: MLX42 library not found at $(MLX42_LIB)"; \
		echo "Please build MLX42 first:"; \
		echo "cd $(MLX42_DIR) && cmake -B build && cmake --build build -j4"; \
		exit 1; \
		fi

$(NAME): $(MLX42_LIB) $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(GRAPHICS_LIBS) -L ./$(LIBFT_DIR) -lft $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -Iinclude -c $< -o $@

$(OBJ_DIR)/%.o: src/parse/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -Iinclude -c $< -o $@

$(OBJ_DIR)/%.o: src/utils/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -Iinclude -c $< -o $@

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
