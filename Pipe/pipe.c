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
	int	i;
	int	j;
	t_cmd	*lst;

	j = 0;
	lst = lst_cmd;
	while (lst)
	{
		printf("cmd[%d] : %s\n", j, lst->cmd);
		printf("flag[%d] : %d\n", j, lst->flag);
		i = 0;
		while (lst->argv[i])
		{
			printf("arg : %s\n", lst->argv[i]);
		i++;
		}
		j++;
		lst = lst->next;
	}
}

int	execute_pipe(t_cmd *cmd)
{
	pid_t	process1;
	pid_t	process2;
	t_cmd	*second;
	int		pipefd[2];

	print_cmd(cmd);
	cmd->argv[0] = join("/bin/", cmd->argv[0]);
	if (cmd->next->next)
	{
		second = cmd->next->next;
		second->argv[0] = join("/bin/", second->argv[0]);
	}
	else
		return (-1);
	if (pipe(pipefd) == -1)
	{
		write(STDERR_FILENO, "parent: Failed to create pipe\n", 30);
		return (-1);
	}
	process1 = fork();
	if (process1 == 0)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			fprintf(stderr, "ls dup2 failed\n");
			return (-1);
		}
		close(pipefd[0]);
		execve(cmd->argv[0], cmd->argv, cmd->env);
	}
	if (process1 == -1)
	{
		write(STDERR_FILENO, "parent: Could not fork process to run grep\n", 44);
		return (-1);
	}
	else
	{
		process2 = fork();
		if (process2 == 0)
		{
			if (dup2(pipefd[0], STDIN_FILENO) == -1)
			{
				fprintf(stderr, "child: grep dup2 failed\n");
				return (-1);
			}
			close(pipefd[1]);
			execve(second->argv[0], second->argv, second->env);
		}
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
