# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eteyssed <eteyssed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/24 18:24:10 by eteyssed          #+#    #+#              #
#    Updated: 2015/01/29 17:44:35 by eteyssed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol
SRC		=	main.c line.c libmlx.c
OBJ		=	$(SRC:.c=.o)
HDR		=	libft/
MLX		=	-L/usr/X11/lib -lmlx -lXext -lX11
FLAGS	=	-Wall -Wextra -Werror
CC		=	gcc

all: $(NAME)

%.o: %.c
	@$(CC) -O4 $(FLAGS) -I $(HDR) -I . -o $@ -c $? -I /opt/X11/include/

$(NAME): $(OBJ)
	@make -C libft/ fclean
	@make -C libft/
	@$(CC) -O4 $(FLAGS) $(MLX) -o $(NAME) $(OBJ) libft/libft.a -g
	@echo "Sucess: Program compiled." 

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
