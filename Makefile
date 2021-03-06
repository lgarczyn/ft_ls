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

OBJ =  $(addprefix obj/, $(SRC:.c=.o))

FLG = -Wall -Werror -Wextra

LIB = -L libft/ -lft

DEB =

OPT = -Os -flto -march=native

all:
	mkdir -p obj
	$(MAKE) -j8 $(NAME)

libft:

$(NAME):$(OBJ)
	cd libft && make -j8
	gcc $(FLG) $(OPT) $(OBJ) $(LIB) $(DEB) -o $(NAME)
	
obj/%.o: %.c ft_ls.h Makefile
	gcc $(FLG) $(OPT) $(DEB) -c $< -o $@

clean:
	rm -rf $(OBJ)
	cd libft && make clean

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)
	cd libft && make fclean

re:
	$(MAKE) fclean
	$(MAKE) all
