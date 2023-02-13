/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:29:27 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/13 17:35:10 by npiya-is         ###   ########.fr       */
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
# include <termios.h>
# include "libft/libft.h"
# include "token.h"
# include "color.h"

typedef struct s_global
{
	int		fds;
	int		redir;
	int		fd;
	int		pipe[2];
	char	*cwd;
	char	*prompt;
	char	*arg;
	char	**env;
}	t_global;

extern t_global	g_all;

typedef struct s_token
{
	struct s_token	*right;
	struct s_token	*left;
	char			*input;
	char			*token;
	int				track;
	int				flag;
}	t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**argv;
	char			**env;
	int				flag;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*assign_cmd(t_cmd *lst_cmd, t_token *cmd, char **envp);
void	shift_re_append_cmd(t_cmd **cmd);
void	re_append_cmd(t_cmd **cmd);
void	assign_argv(t_cmd *lst, char **envp);
void	assign_flag(char *param, t_token *cmd);
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
void	redir_heredoc(t_cmd **cmd);
void	remove_cmd(t_cmd **cmd, t_cmd *rem);
void	shift_inheredoc(t_cmd **cmd);
void	shift_path(char *path);
void	shift_reappend(t_cmd **cmd);
void	execute_cmd(t_cmd *lst_cmd);
void	sig_handle(int signo, siginfo_t *info, void *ucontext);
void	sig_hand_main(void);
void	free_split(char **spl);
void	free_lstcmd(t_cmd *cmd);
void	*ft_realloc(void *ptr, int size);
void	print_split(char **argv);
void	change_env(char *argv);
void	close_fd(t_cmd *cmd, int *pipefd);
int		exit_implement(char *arg, t_token *token, t_cmd *cmd, char **envp);
int		argv_len(char **arg);
int		check_flag(int flag);
int		ft_isspace(char c);
int		check_pipe(char arg);
int		check_orcmd(char arg1, char arg2);
int		check_meta(char meta);
int		check_arg(char meta1, char meta2);
int		find_meta(char *param);
int		find_index(char *param, int meta);
int		find_nextarg(char *param);
int		cd_implement(t_cmd *cmd);
int		is_builtin_parent(t_cmd *cmd);
int		is_builtin_child(t_cmd *cmd);
int		assign_pathcmd(t_cmd *cmd, char *command);
int		size_argquote(char *param, int sign);
int		find_envars(char *token);
int		find_quoteindex(char *token, char sign);
int		envar_len(char *token);
int		envartoken_size(char *token);
int		envar_size(char *token);
int		find_envindex(char *env);
int		echo_implement(t_cmd *cmd);
int		export_implement(t_cmd *cmd);
int		env_implement(char **env);
int		unset_implement(t_cmd *cmd);
int		pwd_implement(void);
int		count_redir(t_cmd *cmd);
int		redir(t_cmd *cmd);
int		check_flagredir(int flag);
char	*find_env(char *env);
char	*arrange_cmd(char *param);
char	*assign_token(char *param, t_token *cmd, int i);
char	*trim_character(char *param);
char	*arrange_cmd(char *param);
char	*trim_space(char *param);
char	*find_token(char *param, t_token *cmd);
char	*copy_meta(char	*param, int sign);
char	*copy_arg(char *param, int len);
char	*find_path(t_cmd *cmd);
char	**create_argv(char *param, int size);
char	**argv_join(char **arg1, char **arg2);
char	**free_argv(char **a, char **b, char **(*f)(char **, char **));
char	*check_envar(char *token);
char	*ft_getenv(char *str);
char	*copy_envar(char *token, int sign, int size);
char	**copy_env(char **envp);
char	*getenv_str(char *token, int start, size_t len);
char	*free_str(char *a, char *b, char *(*f)(const char *, const char *));
t_cmd	*build_cmd(t_cmd *lst_cmd, t_token *cmd, char **envp);
t_cmd	*shift_redir(t_cmd *cmd, int times);

#endif