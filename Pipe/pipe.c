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

int	redir;
int	fds;

void	pipe_cmd(t_cmd *cmd, int *pipefd)
{
	dup2(g_all.fds, STDIN_FILENO);
	close(g_all.fds);
	if (cmd->next && cmd->next->flag == PIPE)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	shift_reappend(t_cmd **cmd)
{
	if ((*cmd)->next)
	{
		if ((*cmd)->flag == REDIR_OUT || (*cmd)->next->flag == APPEND)
		{
			if ((*cmd)->flag == REDIR_OUT)
				(*cmd) = (*cmd)->next;
		}
		while ((*cmd)->next && ((*cmd)->next->flag == REDIR_OUT || (*cmd)->next->flag == APPEND))
		{
			if ((*cmd)->next->next && (*cmd)->next->flag == REDIR_OUT)
			{
				if (argv_len((*cmd)->next->next->argv) > 1)
				{
					(*cmd)->argv = argv_join((*cmd)->argv, &(*cmd)->next->next->argv[1]);
					remove_cmd(cmd, (*cmd)->next);
				}
				remove_cmd(cmd, (*cmd)->next);
			}
		}
	}
}

void	re_append(t_cmd **cmd)
{
	if ((*cmd)->next)
	{
		if ((*cmd)->flag == REDIR_OUT || (*cmd)->flag == APPEND)
		{
			if ((*cmd)->flag == REDIR_OUT)
			{
				g_all.redir = open((*cmd)->next->argv[0], \
						O_WRONLY | O_CREAT | O_TRUNC, 0666);
				(*cmd) = (*cmd)->next;
			}
			dup2(g_all.redir, STDOUT_FILENO);
			close(g_all.redir);
		}
		while ((*cmd)->next && ((*cmd)->next->flag == REDIR_OUT || (*cmd)->next->flag == APPEND))
		{
			if ((*cmd)->next->next && (*cmd)->next->flag == REDIR_OUT)
			{
				g_all.redir = open((*cmd)->next->next->argv[0], \
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
			}
			else if ((*cmd)->next->next && (*cmd)->next->flag == APPEND)
			{
				g_all.redir = open((*cmd)->next->next->argv[0], \
					O_WRONLY | O_CREAT | O_APPEND, 0666);
			}
			if ((*cmd)->next && (*cmd)->next->next)
			{
				if (argv_len((*cmd)->next->next->argv) > 1)
				{
					(*cmd)->argv = argv_join((*cmd)->argv, &(*cmd)->next->next->argv[1]);
					remove_cmd(cmd, (*cmd)->next);
				}
				remove_cmd(cmd, (*cmd)->next);
			}
			dup2(g_all.redir, STDOUT_FILENO);
			close(g_all.redir);
		}
	}
	dup2(0, g_all.redir);
}

void	close_fd(t_cmd *cmd, int *pipefd)
{
	if (!(cmd->next && cmd->next->flag == PIPE))
		dup2(0, g_all.fds);
	if (cmd->next && cmd->next->flag == PIPE)
	{
		dup2(pipefd[0], g_all.fds);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	execute(t_cmd *cmd)
{
	pid_t	process;
	int		pipefd[2];
	int		i;

	i = 0;
	if (cmd && cmd->next && cmd->next->flag == PIPE)
		pipe(pipefd);
	if (is_builtin_parent(cmd))
		return ;
	process = fork();
	if (process < 0)
		printf("fork error\n");
	if (process == 0)
	{
		pipe_cmd(cmd, pipefd);
		re_append(&cmd);
		redir_heredoc(&cmd);
		if (cmd->argv)
		{
			while (cmd->argv[i] && !assign_pathcmd(cmd, cmd->argv[i]))
				i++;
			if (!assign_pathcmd(cmd, cmd->argv[i]))
			{
				dprintf(2, "test\n");
				perror("command not found");
			}
			if (is_builtin_child(cmd))
				return ;
			if (execve(cmd->argv[0], &cmd->argv[i], cmd->env) == -1)
				perror("execve error");
		}
	}
	close_fd(cmd, pipefd);
}
