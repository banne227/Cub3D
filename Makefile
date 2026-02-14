# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banne <banne@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/09 15:02:14 by banne             #+#    #+#              #
#    Updated: 2026/02/13 17:17:35 by banne            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -Iincludes -Iincludes/minilibx-linux -Isrc/libft -Isrc/libft/ft_printf -Isrc/libft/gnl -g3
LDFLAGS     = -Lincludes/minilibx-linux -lmlx -lX11 -lXext -lm
RM          = rm -f

LIBFT_DIR   = src/libft
LIBFT       = $(LIBFT_DIR)/libft.a
MLX_DIR     = includes/minilibx-linux
MLX         = $(MLX_DIR)/libmlx.a

SRCS        = src/main.c \
              src/initializer/init_data.c \
              src/initializer/init_mlx.c \
              src/parsing/parsing.c \
              src/parsing/file_checker.c \
              src/parsing/get_data.c \
              src/parsing/get_map.c \
              src/parsing/get_value.c \
              src/parsing/verif_map.c \
			  src/parsing/verif_data.c \
			  src/utils/copy.c \
			  src/utils/free.c \
			  src/render/minimap/minimap.c \
			  src/render/render.c \
			  src/game/needed.c \
			  src/game/mouvement.c \
			  src/render/menu/menu.c \
			  src/render/menu/enter.c \
			  src/utils/time.c \
			  src/audio/audio.c \
			  src/initializer/player_pos.c \
			  src/initializer/init_game.c \
			  src/initializer/load_weapons.c \
			  src/weapons/draw_weapons.c \

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ] || [ ! -f "$(MLX_DIR)/configure" ]; then \
		echo "Cloning minilibx-linux..."; \
		rm -rf $(MLX_DIR); \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	cd $(MLX_DIR) && ./configure
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(MLX) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	-$(MAKE) -C $(MLX_DIR) clean

c:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	-$(MAKE) -C $(MLX_DIR) clean
	clear
	
fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_DIR)/libft.a
	-$(MAKE) -C $(MLX_DIR) fclean

re: fclean all

r: fclean all c

.PHONY: all clean fclean re