/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:47:42 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/25 18:57:32 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_heredoc(t_cmd *cmd)
{
	if (cmd->next)
	{
		while (cmd->next && (cmd->next->flag == REDIR_IN || cmd->next->flag == HEREDOC))
		{
			if (cmd->next->next && cmd->next->flag == REDIR_IN)
			{
				redir = open(cmd->next->next->argv[0], O_RDONLY);
				if (argv_len(cmd->next->next->argv) > 1)
				{
					cmd->argv = argv_join(cmd->argv, &cmd->next->next->argv[1]);
					remove_cmd(&cmd, cmd->next);
					remove_cmd(&cmd, cmd->next);
				}
				dup2(redir, STDIN_FILENO);
				close(redir);
			}
			else if (cmd->next->next && cmd->next->flag == HEREDOC)
			{
				if (argv_len(cmd->next->next->argv) > 1)
				{
					cmd->argv = argv_join(cmd->argv, &cmd->next->next->argv[1]);
					remove_cmd(&cmd, cmd->next->next);
					remove_cmd(&cmd, cmd->next);
				}
				dup2(redir, STDOUT_FILENO);
				close(redir);
			}
		}
	}
}

void	shift_inheredoc(t_cmd *cmd)
{
	if (cmd->next)
	{
		while (cmd->next && (cmd->next->flag == REDIR_IN || cmd->next->flag == HEREDOC))
		{
			if (cmd->next->next && cmd->next->flag == REDIR_IN)
			{
				if (argv_len(cmd->next->next->argv) > 1)
				{
					remove_cmd(&cmd, cmd->next);
					remove_cmd(&cmd, cmd->next);
				}
			}
			else if (cmd->next->next && cmd->next->flag == HEREDOC)
			{
				if (argv_len(cmd->next->next->argv) > 1)
				{
					remove_cmd(&cmd, cmd->next->next);
					remove_cmd(&cmd, cmd->next);
				}
			}
		}
	}
}
