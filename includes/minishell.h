/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:29:27 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:46:47 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/param.h>
# include <sys/syslimits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include "../libft/libft.h"
# include "token.h"
# include "color.h"
# include "redir.h"
# include "expander.h"
# include "builtin.h"
# include "shell_types.h"
# include "error_msg.h"

extern t_global	g_all;

char	*read_arg(void);
void	access_error(t_cmd *cmd, char *error);
void	set_shellatt(void);
void	reset_shellatt(void);
void	assign_argv(t_cmd *lst, char **envp);
void	assign_nexttoken(t_token *cmd);
void	build_token(t_token *cmd, char *param);
void	execute(t_cmd *cmd);
void	free_cmd(t_token *cmd);
void	ft_free(t_cmd *cmd);
void	gettoken(char *param, t_token *cmd);
void	initialize_cmd(t_cmd *cmd, char **env);
void	initilize_token(t_token *cmd);
void	parsing(char *arg, char **envp, t_token *cmd);
void	print_cmd(t_cmd *lst_cmd);
void	print_token(t_token *cmd);
void	remove_cmd(t_cmd **cmd, t_cmd *rem);
void	shift_path(char *path);
void	execute_cmd(t_cmd *lst_cmd);
void	sig_handle(int signo, siginfo_t *info, void *ucontext);
void	sig_child_handle(int signo, siginfo_t *info, void *ucontext);
void	sig_hand_main(void);
void	sig_hand_child(void);
void	free_split(char **spl);
void	free_lstcmd(t_cmd *cmd);
void	print_split(char **argv);
void	change_env(char *argv);
void	close_fd(t_cmd *cmd, int *pipefd);
void	run_process(t_token *cmd);
int		check_flag(int flag);
int		ft_isspace(char c);
int		check_pipe(char arg);
int		check_orcmd(char arg1, char arg2);
int		check_arg(char meta1, char meta2);
int		find_index(char *param, int meta);
int		find_nextarg(char *param);
int		find_envindex(char *env);
char	*find_env(char *env);
char	*arrange_cmd(char *param);
char	*trim_character(char *param);
char	*trim_space(char *param);
char	*copy_arg(char *param, int len);
char	**create_argv(char *param, int size);
char	*check_envar(char *token);
char	*ft_getenv(char *str);
char	**copy_env(char **envp);
char	*free_str(char *a, char *b, char *(*f)(const char *, const char *));
t_cmd	*build_cmd(t_cmd *lst_cmd, t_token *cmd, char **envp);
t_cmd	*assign_cmd(t_cmd *lst_cmd, t_token *cmd, char **envp);

#endif