# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rymuller <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/20 12:31:51 by rymuller          #+#    #+#              #
#    Updated: 2019/06/20 13:46:44 by rymuller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 := checker
NAME2 := push_swap

SRC :=	check_argv_and_placing_stack.c \
		doubly_linked_list_for_pvt_stack_b.c \
		doubly_linked_list_for_stacks.c \
		quicksort.c \
		push.c \
		swap.c \
		rotate.c \
		reverse_rotate.c \

CFLAGS := -Wall -Wextra -Werror
HEADER := -I./libft/includes
LIB := -L./libft -lft -L./ft_printf -lftprintf

all: $(NAME1) $(NAME2)

$(NAME1): $(SRC)
	make -C libft
	make -C ft_printf
	gcc $(CFLAGS) $(HEADER) $(SRC) checker.c $(LIB) -o $(NAME1)

$(NAME2): $(SRC)
	gcc $(CFLAGS) $(HEADER) $(SRC) push_swap.c $(LIB) -o $(NAME2)

clean:
	make -C libft clean
	make -C ft_printf clean

fclean: clean
	rm -rf $(NAME1) $(NAME2)
	make -C libft fclean
	make -C ft_printf fclean

re: fclean all

.PHONY: clean flcean all re

ARG=$(ruby -e "puts (1..100).to_a.shuffle.join(' ')")
