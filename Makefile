# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 12:14:08 by mayyildi          #+#    #+#              #
#    Updated: 2023/04/11 22:25:12 by sroggens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	main.c								\
		utils/env_prep.c					\
		utils/env_utils.c					\
		utils/error_msg.c					\
		utils/ft_free_arr.c					\
		utils/ft_getenv.c					\
		utils/ft_print_arr.c				\
		utils/ft_update_env.c				\
		utils/list_prep.c					\
		utils/list_utils.c					\
		utils/update_retval.c				\
		utils/va_env.c						\
		parsing/forbidden_char_check.c		\
		parsing/forbidden_char_checkbis.c	\
		parsing/lexer.c						\
		parsing/lexerbis.c					\
		parsing/parsing_check.c				\
		parsing/parsing.c					\
		parsing/quotes_check.c				\
		parsing/quotes_prep.c				\
		parsing/single_quote.c				\
		parsing/single_quotebis.c			\
		minilib/ft_atoi.c					\
		minilib/ft_bzero.c					\
		minilib/ft_calloc.c					\
		minilib/ft_isalnum.c				\
		minilib/ft_isalpha.c				\
		minilib/ft_isdigit.c				\
		minilib/ft_isprint.c				\
		minilib/ft_isspace.c				\
		minilib/ft_itoa.c					\
		minilib/ft_memset.c					\
		minilib/ft_putchar_fd.c				\
		minilib/ft_putstr_fd.c				\
		minilib/ft_split.c					\
		minilib/ft_strchr.c					\
		minilib/ft_strcmp.c					\
		minilib/ft_strdup.c					\
		minilib/ft_strjoin.c				\
		minilib/ft_strlen.c					\
		minilib/ft_strncmp.c				\
		minilib/ft_strrchr.c				\
		execution/heredoc.c					\
		execution/heredocbis.c				\
		execution/heredocbis2.c				\
		execution/path_prep_utils.c			\
		execution/path_prep.c				\
		execution/pipeline.c				\
		execution/pipelinebis.c				\
		execution/pipelinebis2.c			\
		execution/pipes_utils.c				\
		execution/pipes.c					\
		execution/redir.c					\
		execution/signals.c					\
		execution/single_cmd.c				\
		execution/single_pipe.c				\
		execution/singlepipebis.c			\
		builtins/builtin_cd_p.c				\
		builtins/builtin_cd.c				\
		builtins/builtin_echo_utils.c		\
		builtins/builtin_echo.c				\
		builtins/builtin_env.c				\
		builtins/builtin_exit_utils.c		\
		builtins/builtin_exit.c				\
		builtins/builtin_export_utils_bis.c	\
		builtins/builtin_export_utils_bis2.c\
		builtins/builtin_export_utils.c		\
		builtins/builtin_export.c			\
		builtins/builtin_pwd.c				\
		builtins/builtin_unset.c			\
		builtins/dispatch_builtins.c		\
		builtins/dispatch_utils_bis.c		\
		builtins/dispatch_utils.c			\

OBJECTS = $(SRCS:.c=.o)

CC = gcc

READLINE = -L/Users/sroggens/homebrew/opt/readline/lib -lreadline

CFLAGS = -Wall -Werror -Wextra

SFLAGS = -Wall -Werror -Wextra 

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
