# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/11 19:17:02 by swedde            #+#    #+#              #
#    Updated: 2019/12/12 17:35:06 by nsheev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

INC = -I./includes -I./libft/includes

LIB = libft/libft.a

SRC =	src/main.c					\
		src/get_next_line.c			\
		src/set_def_gen.c			\
		src/get_name_and_comment.c	\
		src/write_int_to_file.c		\
		src/do_exit.c 				\
		src/reading.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(SRC)
	gcc -c -I./libft/includes -I./includes $(SRC)
	gcc *.o $(INC) -o asm -L libft/ -lft

$(LIB):
	make -C libft/ fclean && make -C libft/

test: $(NAME) test_bin
	./asm batman.s
	./test_bin batman.cor

test_bin: test/test_main.c
	gcc test/test_main.c -o test_bin

clean:
	make -C libft/ clean
	/bin/rm -f *.o

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME) test_bin

re: fclean all
