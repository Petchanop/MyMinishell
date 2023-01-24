# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/04 17:48:56 by npiya-is          #+#    #+#              #
#    Updated: 2023/01/24 21:31:55 by npiya-is         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc

CFLAGS= -g -Wall -Werror -Wextra

LIBS= -lreadline -L libft -lft

PARS_DIR= parsing/
PIPE_DIR= Pipe/

SRCS_PARS:= $(PARS_DIR)parsing.c \
	$(PARS_DIR)parsing_utils.c \
	$(PARS_DIR)parseexec.c \
	$(PARS_DIR)token.c \
	$(PARS_DIR)checkcmd.c \
	$(PARS_DIR)checkmeta.c \
	$(PARS_DIR)calculate_size.c \
	$(PARS_DIR)manage_token.c \
	$(PIPE_DIR)pipe.c \
	$(PIPE_DIR)access.c \
	$(PIPE_DIR)manage_args.c \
	$(PIPE_DIR)redir.c \
	
SRCS = main_shell.c \
	execute.c \
	clear_memory.c \

NAME= minishell

all: $(NAME)

$(NAME):
	@make -C libft
	$(CC) $(CFLAGS) $(SRCS) $(SRCS_PARS) -o $(NAME) $(LIBS)

fclean:
	@make -C libft fclean
	rm -rf $(NAME) $(NAME).dSYM

re: fclean all 
