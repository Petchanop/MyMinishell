# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/04 17:48:56 by npiya-is          #+#    #+#              #
#    Updated: 2023/02/12 22:16:00 by npiya-is         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc

CFLAGS= -g -Wall -Werror -Wextra

LIBS= -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline -L libft -lft
# LIBS= -Lreadline -Ireadline -lreadline -L libft -lft

PARS_DIR= parsing/
PIPE_DIR= Pipe/
BUILTIN_DIR = builtin/
EXPAND_DIR= expand/
SIGNAL_DIR= signal/

SRCS_PARS:= $(PARS_DIR)parsing.c \
	$(PARS_DIR)parsing_utils.c \
	$(PARS_DIR)parseexec.c \
	$(PARS_DIR)token.c \
	$(PARS_DIR)build_cmd.c \
	$(PARS_DIR)checkcmd.c \
	$(PARS_DIR)checkmeta.c \
	$(PARS_DIR)calculate_size.c \
	$(PARS_DIR)manage_token.c \
	$(PIPE_DIR)pipe.c \
	$(PIPE_DIR)access.c \
	$(PIPE_DIR)manage_args.c \
	$(PIPE_DIR)redir.c \
	$(BUILTIN_DIR)isbuiltin.c \
	$(BUILTIN_DIR)cd.c \
	$(BUILTIN_DIR)echo.c \
	$(BUILTIN_DIR)export.c \
	$(BUILTIN_DIR)unset.c \
	$(BUILTIN_DIR)exit.c \
	$(BUILTIN_DIR)pwd.c \
	$(EXPAND_DIR)expander.c \
	$(EXPAND_DIR)en_var.c \
	$(SIGNAL_DIR)ctrl_c.c \
	
SRCS = main_shell.c \
	execute.c \
	clear_memory.c \
	manage_env.c \

NAME= minishell

all: $(NAME)

$(NAME):
	@make -C libft
	$(CC) $(CFLAGS) $(SRCS) $(SRCS_PARS) -o $(NAME) $(LIBS)

fclean:
	@make -C libft fclean
	rm -rf $(NAME) $(NAME).dSYM

re: fclean all 
