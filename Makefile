# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banne <banne@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/09 15:02:14 by banne             #+#    #+#              #
#    Updated: 2026/02/03 09:18:14 by banne            ###   ########.fr        #
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

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	cd $(MLX_DIR) && ./configure
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
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