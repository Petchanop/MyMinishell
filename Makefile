# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/04 17:48:56 by npiya-is          #+#    #+#              #
#    Updated: 2022/12/08 15:18:17 by npiya-is         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc

CFLAGS= -Wall -Werror -Wextra

LIBS= -lreadline -L libft -lft

SRCS = main_shell.c \
		parsing.c \

NAME= minishell

all: $(NAME)

$(NAME):
	@make -C libft
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIBS)

fclean:
	@make -C libft fclean
	rm -rf $(NAME)

re: fclean all 