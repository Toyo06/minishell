# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sroggens <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 18:46:27 by sroggens          #+#    #+#              #
#    Updated: 2022/11/23 13:23:51 by sroggens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lexer

SRCS = main.c Tool.c Tool_list.c Ft_split.c \
	   Printf_part2.c Printf_part1.c Quote_detector.c \
	   Forbidencharact.c Prepa_list.c Quote_preparator.c \
	   Parsing.c Errormess.c Prepa_env.c Tool_list_env.c \

OBJECTS = $(SRCS:.c=.o)

CC = gcc

READLINEDESESMORT = -L/Users/sroggens/homebrew/opt/readline/lib -lreadline

CFLAGS = -Wall -Werror -Wextra

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
