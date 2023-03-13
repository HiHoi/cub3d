# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 20:01:46 by hoslim            #+#    #+#              #
#    Updated: 2023/03/13 13:07:29 by hoslim           ###   ########.fr        #
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
		srcs/util_free.c\
		srcs/render.c\
		srcs/key.c\
		srcs/ray.c\
		srcs/draw.c\
		srcs/ray_cal.c

HEADER = ./includes/
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
-include $(DEPS)

CC = cc
FLAGS = -Wall -Werror -Wextra -MMD -MP
MLX_NAME = mlx
MLX_DIR = ./mlx
MLX = $(addprefix $(MLX_DIR)/, libmlx.a)
TERMCAP = -lncurses
CLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx

.DEFAULT_GOAL := all

all : $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -I $(HEADER) -I $(MLX_DIR) -c $< -o $@

$(NAME) : $(OBJS)
	$(MAKE) -C $(MLX_DIR) all
	$(CC) $(FLAGS) -L$(MLX_DIR) -l$(MLX_NAME) $(TERMCAP) $(CLIB) -o $(NAME) $(OBJS)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)

clean :
	rm -rf srcs/*.o srcs/parse/*.o $(DEPS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all re clean fclean