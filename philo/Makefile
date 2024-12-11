# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/22 08:59:59 by dvan-hum          #+#    #+#              #
#    Updated: 2024/12/11 12:30:36 by dvan-hum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

#CC = gcc -Wall -Wextra -Werror -O3 -pthread
CC = gcc -Wall -Wextra -Werror -pthread -g -fsanitize=address

SRC = main.c philosopher.c utils.c
OBJ = $(patsubst %.c, obj/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

obj/%.o: src/%.c | ./obj
	$(CC) -c $< -o $@ -I ./

./obj:
	mkdir obj

clean:
	rm -rf ./obj

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all