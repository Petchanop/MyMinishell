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

t_cmd	*execute_pipe(t_cmd *cmd)
{
	pid_t	process1;
	pid_t	process2;
	t_cmd	*second;
	int		pipefd[4];
	int i; 
	int		status;

	// print_cmd(cmd);
	if (pipe(pipefd) == -1)
	{
		write(STDERR_FILENO, "parent: Failed to create pipe\n", 30);
		exit(1);
	}
	i = 0;
	while (cmd->next && cmd->next->flag == PIPE)
	{
		if (cmd->next->next)
			second = cmd->next->next;
		process1 = fork();
		if (process1 < 0)
			printf("fork error\n");
		if (process1 == 0)
		{
			close(pipefd[i]);
			dup2(pipefd[i + 1], STDOUT_FILENO);
			close(pipefd[i + 1]);
			if (!assign_pathcmd(cmd, cmd->argv[0]))
			{
				perror("command not found");
				exit(1);
			}
			printf("cmd : %s\n", cmd->argv[0]);
			if (execve(cmd->argv[0], cmd->argv, cmd->env) == -1)
				printf("kuy1\n");
		}
		else
		{
			process2 = fork();
			if (process2 < 0)
				printf("fork2 error\n");
			if (process2 == 0)
			{
				waitpid(process1, &status, WNOHANG);
				close(pipefd[i + 1]);
				dup2(pipefd[i], STDIN_FILENO);
				close(pipefd[i]);
				if (!assign_pathcmd(second, second->argv[0]))
				{
					perror("command not found");
					exit(1);
				}
				printf("cmd : %s\n", second->argv[0]);
				if (execve(second->argv[0], second->argv, second->env) == -1)
					printf("kuy2\n");
			}
		}
		close(pipefd[i]);
		close(pipefd[i + 1]);
		// print_cmd(cmd);
		cmd = cmd->next->next;
		i += 2;
	}
	return (cmd);
}
