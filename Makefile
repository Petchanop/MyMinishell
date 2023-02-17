# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/04 17:48:56 by npiya-is          #+#    #+#              #
#    Updated: 2023/02/17 22:31:03 by npiya-is         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
CFLAGS= -Wall -Werror -Wextra

LDFLAGS	= -L/usr/local/opt/readline/lib
CPPFLAGS = -I/usr/local/opt/readline/include

LIBS= -L libft -lft

SRCS_DIR= srcs/
PARS_DIR= parsing/
PIPE_DIR= Pipe/
BUILTIN_DIR = builtin/
EXPAND_DIR= expand/
SIGNAL_DIR= signal/

ALL_DIR:= $(PARS_DIR)parsing.c \
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
	$(PIPE_DIR)heredoc.c \
	$(PIPE_DIR)open_fd.c \
	$(BUILTIN_DIR)isbuiltin.c \
	$(BUILTIN_DIR)cd.c \
	$(BUILTIN_DIR)echo.c \
	$(BUILTIN_DIR)export.c \
	$(BUILTIN_DIR)unset.c \
	$(BUILTIN_DIR)exit.c \
	$(BUILTIN_DIR)pwd.c \
	$(EXPAND_DIR)expander.c \
	$(EXPAND_DIR)en_var.c \
	$(SIGNAL_DIR)signal.c \

SRCS = $(SRCS_DIR)main_shell.c \
	$(SRCS_DIR)execute.c \
	$(SRCS_DIR)clear_memory.c \
	$(SRCS_DIR)manage_env.c \
	$(SRCS_DIR)print_cmd.c \
	$(SRCS_DIR)setshellatt.c \
	$(SRCS_DIR)error_msg.c \

OBJS=$(SRCS:%.c=%.o)
OBJS_DIRS=$(ALL_DIR:%.c=%.o)

NAME= minishell

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_DIRS)
	@make -C libft
	$(CC) $(CFLAGS) $(CPPFLAGS) -lreadline $(OBJS) $(OBJS_DIRS) -o $(NAME) $(LIBS)

clean:
	@make -C libft clean
	rm -rf $(OBJS) $(OBJS_DIRS)

fclean:
	@make -C libft fclean
	rm -rf $(NAME) $(NAME).dSYM

re: fclean all 
