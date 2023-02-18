/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:46:00 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/30 23:12:0 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_cmd(t_cmd *cmd, int *pipefd)
{
	if (g_all.in_out == 1)
		return ;
	if (cmd && cmd->next && cmd->next->flag == PIPE)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	run_childprocess(t_cmd *cmd)
{
	int	i;

	i = 0;
	dup2(g_all.fds, STDIN_FILENO);
	close(g_all.fds);
	g_all.redir = redir(cmd);
	check_openerror(cmd);
	if (check_flagredir(cmd->flag))
		cmd = cmd->next;
	pipe_cmd(shift_redir(cmd, g_all.redir), g_all.pipe);
	if (cmd->argv)
	{
		while (cmd->argv[i] && !assign_pathcmd(cmd, cmd->argv[i]))
			i++;
		if (is_builtin_child(cmd))
			return ;
		if (!assign_pathcmd(cmd, cmd->argv[i]))
		{
			access_error(cmd, CMD_NOTFOUND);
			exit(2);
		}
		else if (execve(cmd->argv[0], &cmd->argv[i], cmd->env) == -1)
			exit(1);
	}
}

void	close_fd(t_cmd *cmd, int *pipefd)
{
	if (cmd && !(cmd->next && cmd->next->flag == PIPE))
		dup2(0, g_all.fds);
	if (cmd && cmd->next && cmd->next->flag == PIPE)
	{
		dup2(pipefd[0], g_all.fds);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	execute(t_cmd *cmd)
{
	if (!cmd)
		return ;
	pipe(g_all.pipe);
	if (is_builtin_parent(cmd))
		return ;
	cmd->pid = fork();
	if (cmd->pid < 0)
		printf("fork error\n");
	if (cmd->pid == 0)
		run_childprocess(cmd);
	g_all.redir = count_redir(cmd);
	close_fd(shift_redir(cmd, g_all.redir), g_all.pipe);
}
