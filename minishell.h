/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:29:27 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/10 20:32:08 by npiya-is         ###   ########.fr       */
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
	char			*cmd;
	char			*opt;
	char			*token;
	char			*arg;
	char			*result;
}	t_cmd;

int		parsing(char *arg, char **envp, t_cmd *cmd);
int		ft_isspace(char c);
char	*parseexec(t_cmd *cmd, char **envp);
char	*gettoken(char *str);
char	*find_arg(char *arg);

#endif