# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 12:14:08 by mayyildi          #+#    #+#              #
#    Updated: 2023/03/11 18:10:44 by mayyildi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	${wildcard *.c}				\
		${wildcard minilib/*.c}		\
		${wildcard parsing/*.c}		\
		${wildcard utils/*.c}		\
		${wildcard builtins/*.c}	\
		${wildcard execution/*.c}

OBJECTS = $(SRCS:.c=.o)

CC = gcc

READLINE = #READLINE

CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address

SFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(READLINE) -o $(NAME)

segv: ${OBJECTS}
	$(CC) $(READLINE) $(SFLAGS) $(OBJECTS) -o $(NAME)

clean :
	rm -rf $(OBJECTS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
	rm -rf $(OBJECTS)

.PHONY: all clean fclean re
