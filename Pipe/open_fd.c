/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:35:26 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:38:33 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_heredoc(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd)
	{
		if (cmd->flag == HEREDOC)
			return (i);
		cmd = cmd->next;
		i++;
	}
	return (0);
}

int	open_heredoc(t_cmd *cmd)
{
	encrypt_str(cmd);
	g_all.heredoc = open(cmd->filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	heredoc_implement(cmd);
	g_all.heredoc = open(cmd->filename, O_RDONLY);
	dup2(g_all.heredoc, STDIN_FILENO);
	g_all.in_out = 0;
	return (g_all.heredoc);
}

int	open_in(t_cmd *cmd, int flag)
{
	int	fd;

	fd = 0;
	if (flag == REDIR_OUT)
	{
		fd = open(cmd->argv[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(fd, STDOUT_FILENO);
		g_all.in_out = 1;
	}
	else if (flag == APPEND)
	{
		fd = open(cmd->argv[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
		dup2(fd, STDOUT_FILENO);
		g_all.in_out = 1;
	}
	return (fd);
}

int	open_out(t_cmd *cmd, int flag)
{
	int	fd;

	fd = 0;
	if (flag == REDIR_IN)
	{
		fd = open(cmd->argv[0], O_RDONLY);
		if ((cmd->next && cmd->next->next && (cmd->next->flag != HEREDOC))
			|| !cmd->next)
		{
			if (!cmd->next || cmd->next->flag == REDIR_OUT
				|| cmd->next->flag == PIPE || cmd->next->flag == APPEND)
				dup2(fd, STDIN_FILENO);
		}
		g_all.in_out = 0;
	}
	if (flag == HEREDOC)
		fd = open_heredoc(cmd);
	return (fd);
}

int	opendup_mode(t_cmd *cmd, int flag)
{
	int	fd;

	fd = 0;
	if (cmd->argv)
	{
		if (flag == REDIR_OUT || flag == APPEND)
		{
			fd = open_in(cmd, flag);
			close(g_all.pipe[1]);
		}
		else if (flag == REDIR_IN || flag == HEREDOC)
		{
			fd = open_out(cmd, flag);
			close(g_all.pipe[0]);
		}
	}
	close(fd);
	return (fd);
}
