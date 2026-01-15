# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banne <banne@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/09 15:02:14 by banne             #+#    #+#              #
#    Updated: 2026/01/15 07:54:30 by banne            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -Iincludes -Isrc/libft -Isrc/libft/ft_printf -Isrc/libft/gnl
RM          = rm -f

LIBFT_DIR   = src/libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRCS        = src/main.c \
              src/parsing/parsing.c \
              src/parsing/file_checker.c \
              src/parsing/get_data.c \
              src/parsing/get_map.c \
              src/parsing/get_value.c \
              src/parsing/verif_map.c \
			  src/parsing/verif_data.c 

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

c:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	clear
	
fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_DIR)/libft.a

re: fclean all

r: fclean all c

.PHONY: all clean fclean re