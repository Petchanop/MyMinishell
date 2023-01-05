/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:12:18 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/06 00:50:19 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_process(void)
{
	int	status;

	while (1)
	{
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
		{
			if (status == 0)
			{
				break ;
			}
		}
	}
}

int	execute_cmd(t_cmd *lst_cmd)
{
	while (lst_cmd)
	{
		if (lst_cmd->next)
		{
			if (lst_cmd->next->flag == PIPE)
			{
				execute_pipe(lst_cmd);
				lst_cmd = lst_cmd->next;
			}
		}
		else
			execute(lst_cmd);
		lst_cmd = lst_cmd->next;
		wait_process();
	}
	return (0);
}

int	execute(t_cmd *cmd)
{
	pid_t	process;

	assign_pathcmd(cmd, cmd->argv[0]);
	process = fork();
	if (process == 0)
	{
		if (execve(cmd->argv[0], &cmd->argv[0], cmd->env) == -1)
		{
			write(1, "Error\n", 6);
			return (-1);
		}
	}
	return (0);
}
