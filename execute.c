/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:12:18 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/28 23:17:26 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_cmd *lst_cmd)
{
	// if (lst_cmd->next)
	// {
	// 	if (lst_cmd->next->flag == PIPE)
	// 		execute_pipe(lst_cmd);
	// }
	// else
		execute(lst_cmd);
	int status;
	while (1)
	{
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
		{
			if (status == 0)
				break ;
		}
	}
	return (0);
}

int	execute(t_cmd *cmd)
{
	int i = 0;
	pid_t	process;

	cmd->argv[0] = join("/bin/", cmd->argv[0]);
	process = fork();
	if (process == 0)
	{
		if (execve(cmd->argv[0], cmd->argv, cmd->env) == -1)
			write(1, "Error\n", 6);
		free(cmd->cmd);
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd);
	}
	return (0);
}
