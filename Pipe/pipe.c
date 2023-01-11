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
		dprintf(2,"cmd[%d] : %s\n", j, lst->cmd);
		dprintf(2,"flag[%d] : %d\n", j, lst->flag);
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

pid_t	execute_pipe(t_cmd *cmd)
{
	pid_t	process;
	int		pipefd[2];

	if (cmd->next && cmd->next->flag == PIPE)
		pipe(pipefd);
	process = fork();
	if (process < 0)
		printf("fork error\n");
	if (process == 0)
	{
		dup2(fds, STDIN_FILENO);
		close(fds);
		if (cmd->next && cmd->next->flag == PIPE)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		if (!assign_pathcmd(cmd, cmd->argv[0]))
		{
			perror("command not found");
			exit(1);
		}
		execve(cmd->argv[0], cmd->argv, cmd->env);
	}
	if (!(cmd->next && cmd->next->flag == PIPE))
		dup2(0, fds);
	if (cmd->next && cmd->next->flag == PIPE)
	{
		dup2(pipefd[0], fds);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	return (process);
}
