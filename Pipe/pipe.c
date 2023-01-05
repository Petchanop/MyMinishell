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

	// print_cmd(cmd);
	if (!assign_pathcmd(cmd, cmd->argv[0]))
	{
		perror("command not found");
		exit(1);
	}
	if (cmd->next->next)
	{
		second = cmd->next->next;
		assign_pathcmd(second, second->argv[0]);
	}
	else
		return (-1);
	if (pipe(pipefd) == -1)
	{
		write(STDERR_FILENO, "parent: Failed to create pipe\n", 30);
		return (-1);
	}
	dprintf(2, "yes\n");
	process1 = fork();
	if (process1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(cmd->argv[0], cmd->argv, cmd->env);
		return (0);
	}
	else
	{
		dprintf(2, "yes2\n");
		process2 = fork();
		if (process2 == 0)
		{
			wait(NULL);
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			execve(second->argv[0], second->argv, second->env);
			return (0);
		}
	}
	close(pipefd[0]);	
	close(pipefd[1]);	
	return (0);
}
