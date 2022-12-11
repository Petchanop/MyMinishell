# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/04 17:48:56 by npiya-is          #+#    #+#              #
#    Updated: 2022/12/10 16:57:15 by npiya-is         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc

CFLAGS= -g -Wall -Werror -Wextra

LIBS= -lreadline -L libft -lft

PARS_DIR= parsing/

SRCS_PARS:= $(PARS_DIR)parsing.c \
	$(PARS_DIR)parsing_utils.c \
	$(PARS_DIR)parseexec.c \

SRCS = main_shell.c \

NAME= minishell

all: $(NAME)

$(NAME):
	@make -C libft
	$(CC) $(CFLAGS) $(SRCS) $(SRCS_PARS) -o $(NAME) $(LIBS)

fclean:
	@make -C libft fclean
	rm -rf $(NAME) $(NAME).dSYM

re: fclean all 
