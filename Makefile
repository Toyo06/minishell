# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 18:46:27 by sroggens          #+#    #+#              #
#    Updated: 2022/11/25 09:39:29 by mayyildi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lexer

SRCS = ${wildcard *.c}

OBJECTS = $(SRCS:.c=.o)

CC = gcc

READLINEDESESMORT = -L/Users/sroggens/homebrew/opt/readline/lib -lreadline

CFLAGS = -Wall -Werror -Wextra #-fsanitize=address

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(READLINEDESESMORT) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean :
	rm -rf $(OBJECTS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
	rm -rf $(OBJECTS)

.PHONY: all clean fclean re
