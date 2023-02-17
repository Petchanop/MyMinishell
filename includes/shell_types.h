/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:23:49 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 17:23:10 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_TYPES_H
# define SHELL_TYPES_H

# include <sys/types.h>

typedef struct s_global
{
	int				fds;
	int				redir;
	int				fd;
	int				in_out;
	int				heredoc;
	int				pid;
	int				pipe[2];
	int				status;
	char			*cwd;
	char			*prompt;
	char			*arg;
	char			**env;
	char			*filename;
	struct termios	term;
	struct termios	shell;
}	t_global;

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
	char			*filename;
	char			**argv;
	char			**env;
	int				flag;
	int				fd;	
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

#endif