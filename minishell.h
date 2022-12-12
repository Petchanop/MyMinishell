/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:29:27 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/12 18:56:47 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "token.h"
# include "color.h"

typedef struct s_cmd
{
	struct s_cmd	*right;
	struct s_cmd	*left;
	char			*input;
	char			*cmd;
	char			*opt;
	int				token;
	char			*arg;
	char			*result;
}	t_cmd;

void	gettoken(char *param, t_cmd *cmd);
void	assign_nextcmd(t_cmd *cmd);
int		parsing(char *arg, char **envp, t_cmd *cmd);
int		ft_isspace(char c);
int		trim_space(char *param);
int		check_pipe(char arg);
int		find_token(char *param, t_cmd *cmd);
int		check_orcmd(char arg1, char arg2);
int		check_arg(char meta1, char meta2);
char	*parseexec(t_cmd *cmd, char **envp);
char	*find_arg(char *arg, t_cmd *cmd);

#endif