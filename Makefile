# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/22 17:11:22 by lgarczyn          #+#    #+#              #
#    Updated: 2015/01/22 17:13:56 by lgarczyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC =	args.c \
		fail.c \
		file.c \
		fill.c \
		free.c \
		main.c \
		node.c \
		path.c \
		show.c \
		sort.c \
		link.c \
		perm.c \
		view.c \
		
OBJ = $(SRC:.c=.o)

FLG = -Wall -Werror -Wextra

LIB = -L libft/ -lft

DEB = 

OPT = -O2

all: $(NAME)

libft:

$(NAME):$(OBJ)
	cd libft && make
	gcc $(FLG) $(OPT) $(OBJ) $(LIB) $(DEB) -o $(NAME)
	
%.o: %.c ft_ls.h
	gcc $(FLG) $(OPT) $(DEB) -c $< $

clean:
	rm -rf $(OBJ)
	cd libft && make clean

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)
	cd libft && make fclean

re: fclean all

optire: fclean opti