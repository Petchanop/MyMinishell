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

void	print_cmd(t_cmd *lst_cmd)
{
	int		i;
	int		j;
	t_cmd	*lst;

	j = 0;
	lst = lst_cmd;
	while (lst)
	{
		dprintf(2, "cmd[%d] : %s\n", j, lst->cmd);
		dprintf(2, "flag[%d] : %d\n", j, lst->flag);
		i = 0;
		while (lst->argv[i])
		{
			dprintf(2, "arg : %s\n", lst->argv[i]);
		i++;
		}
		j++;
		lst = lst->next;
	}
}

void	pipe_cmd(t_cmd *cmd, int *pipefd)
{
	dup2(fds, STDIN_FILENO);
	close(fds);
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
				redir = open((*cmd)->next->argv[0], \
						O_WRONLY | O_CREAT | O_TRUNC, 0666);
				(*cmd) = (*cmd)->next;
			}
			dup2(redir, STDOUT_FILENO);
			close(redir);
		}
		while ((*cmd)->next && ((*cmd)->next->flag == REDIR_OUT || (*cmd)->next->flag == APPEND))
		{
			if ((*cmd)->next->next && (*cmd)->next->flag == REDIR_OUT)
			{
				redir = open((*cmd)->next->next->argv[0], \
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
			}
			else if ((*cmd)->next->next && (*cmd)->next->flag == APPEND)
			{
				redir = open((*cmd)->next->next->argv[0], \
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
			dup2(redir, STDOUT_FILENO);
			close(redir);
		}
	}
	dup2(0, redir);
}

void	close_fd(t_cmd *cmd, int fds, int *pipefd)
{
	if (!(cmd->next && cmd->next->flag == PIPE))
		dup2(0, fds);
	if (cmd->next && cmd->next->flag == PIPE)
	{
		dup2(pipefd[0], fds);
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
	if (cmd->next && cmd->next->flag == PIPE)
		pipe(pipefd);
	process = fork();
	if (process < 0)
		printf("fork error\n");
	if (process == 0)
	{
		pipe_cmd(cmd, pipefd);
		re_append(&cmd);
		redir_heredoc(cmd);
		while (!assign_pathcmd(cmd, cmd->argv[i]))
			i++;
		if (!assign_pathcmd(cmd, cmd->argv[i]))
		{
			perror("command not found");
			exit(1);
		}
		if (execve(cmd->argv[0], &cmd->argv[i], cmd->env) == -1)
			perror("execve error");
	}
	close_fd(cmd, fds, pipefd);
}
