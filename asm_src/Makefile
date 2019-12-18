# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swedde <swedde@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/11 19:17:02 by swedde            #+#    #+#              #
#    Updated: 2019/12/18 01:43:04 by swedde           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

INC = -I./includes -I./libft/includes

LIB = libft/libft.a

SRC =	src/main.c					\
		src/get_next_line.c			\
		src/set_def_gen.c			\
		src/write_int_to_file.c		\
		src/do_exit.c 				\
		src/reading.c				\
		src/t_token_func.c 			\
		src/char_to_string.c 		\
		src/print_point.c 			\
		src/lexical_analyz.c 		\
		src/recording.c 			\
		src/write_short_to_file.c

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
