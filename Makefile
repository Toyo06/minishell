# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sroggens <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 18:46:27 by sroggens          #+#    #+#              #
#    Updated: 2022/11/24 11:47:47 by sroggens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lexer

SRCS = main.c Tool.c Tool_list.c Ft_split.c \
	   Printf_part2.c Printf_part1.c Quote_detector.c \
	   Forbidencharact.c Prepa_list.c Quote_preparator.c \
	   lexer.c Errormess.c Prepa_env.c Tool_list_env.c \
	   Tool_bis.c Parsing.c pwd.c \

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
