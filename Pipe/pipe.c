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

#include "../minishell.h"



void	pipe_cmd(t_cmd *cmd, int *pipefd)
{
	if (cmd && cmd->next && cmd->next->flag == PIPE)
	{
		dprintf(2, "%s dup in\n", cmd->argv[0]);
		// dup2(g_all.fds, STDIN_FILENO);
		// close(g_all.fds);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	close_fd(t_cmd *cmd, int *pipefd)
{
	if (cmd && !(cmd->next && cmd->next->flag == PIPE))
	{
		dprintf(2,  "%s dup back\n", cmd->argv[0]);
		dup2(0, g_all.fds);
	}
	if (cmd && cmd->next && cmd->next->flag == PIPE)
	{
		dprintf(2,  "%s dup pipe\n", cmd->argv[0]);
		dup2(pipefd[0], g_all.fds);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	execute(t_cmd *cmd)
{
	// int		pipefd[2];
	int		i;

	i = 0;
	if (!cmd)
		return ;
	// if (cmd && cmd->next->flag == PIPE)
	pipe(g_all.pipe);
	if (is_builtin_parent(cmd))
		return ;
	cmd->pid = fork();
	if (cmd->pid < 0)
		printf("fork error\n");
	if (cmd->pid == 0)
	{
		dup2(g_all.fds, STDIN_FILENO);
		close(g_all.fds);
		g_all.redir = redir(cmd);
		if (check_flagredir(cmd->flag))
			cmd = cmd->next;
		//print_cmd(shift_redir(cmd, g_all.redir));
		pipe_cmd(shift_redir(cmd, g_all.redir), g_all.pipe);
		if (cmd->argv)
		{
			while (cmd->argv[i] && !assign_pathcmd(cmd, cmd->argv[i]))
				i++;
			if (!assign_pathcmd(cmd, cmd->argv[i]))
			{
				perror("command not found");
				exit(1);
			}
			if (is_builtin_child(cmd))
				return ;
			if (execve(cmd->argv[0], &cmd->argv[i], cmd->env) == -1)
				perror("execve error");
		}	
	}
	g_all.redir = count_redir(cmd);
	close_fd(shift_redir(cmd, g_all.redir), g_all.pipe);
}
