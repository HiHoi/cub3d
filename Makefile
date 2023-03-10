# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 20:01:46 by hoslim            #+#    #+#              #
#    Updated: 2023/03/10 21:32:43 by hoslim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRCS = \
		srcs/parse/get_next_line_utils.c\
		srcs/parse/get_next_line.c\
		srcs/parse/parse_map.c\
		srcs/main.c\
		srcs/ft_util.c\
		srcs/ft_util2.c\
		srcs/init.c\
		srcs/utils.c\
		srcs/render.c\
		srcs/key.c\
		srcs/ray.c

HEADER = includes
OBJS = $(SRCS:.c=.o)
CC = gcc
FLAGS = -Wall -Werror -Wextra -fsanitize=undefined -g
MLX_NAME = mlx
MLX_DIR = ./mlx
MLX = $(addprefix $(MLX_DIR)/, libmlx.a)
CLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx

all : $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -I $(HEADER) -I$(MLX_DIR) -c $< -o $@

$(NAME) : $(OBJS)
	$(MAKE) -C $(MLX_DIR) all
	$(CC) $(FLAGS) $(CLIB) -o $(NAME) $(OBJS) -L$(MLX_DIR) -l$(MLX_NAME)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)

clean :
	rm -rf srcs/*.o srcs/parse/*.o

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all re clean fclean