/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:29:27 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/12 00:44:38 by npiya-is         ###   ########.fr       */
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
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "libft/libft.h"
# include "token.h"
# include "color.h"

int fds;
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
	struct s_cmd	*next;
}	t_cmd;

void	print_cmd(t_cmd *lst_cmd);
void	assign_flag(char *param, t_token *cmd);
void	gettoken(char *param, t_token *cmd);
void	assign_nexttoken(t_token *cmd);
void	build_token(t_token *cmd, char **envp);
void	assign_argv(t_cmd *lst, char **envp);
pid_t	execute_pipe(t_cmd *cmd);
void	free_cmd(t_cmd *cmd);
int		ft_isspace(char c);
int		check_pipe(char arg);
int		check_orcmd(char arg1, char arg2);
int		check_meta(char meta);
int		check_arg(char meta1, char meta2);
int		calculate_size(char *param);
int		find_arglen(char *param);
int		find_meta(char *param);
int		execute_cmd(t_cmd *lst_cmd);
int		execute(t_cmd *cmd);
int		assign_pathcmd(t_cmd *cmd, char *command);
char	*trim_space(char *param);
char	*join(const char *s1, const char *s2);
char	*find_token(char *param, t_token *cmd);
char	*copy_meta(char	*param);
char	*copy_arg(char *param, int len);
char	*build_quotecmd(t_token *cmd, char *argv);
char	**create_argv(char *param, int size);
char	*find_path(t_cmd *cmd);
void	parsing(char *arg, char **envp, t_token *cmd);
t_cmd	*build_cmd(t_cmd *lst_cmd, t_token *cmd, char **envp);

#endif