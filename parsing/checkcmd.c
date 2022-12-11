/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 00:21:19 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/12 00:21:24 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe(char arg)
{
	return (arg == PIPE);
}

int	check_orcmd(char arg1, char arg2)
{
	if (arg1 == PIPE && arg2 == PIPE)
		return (PIPE);
}

int	check_arg(t_cmd *cmd, char **envp)
{
	int	i;

	i = 0;
	printf("cmd : %s\narg : %s\n", cmd->cmd, cmd->arg);
	while (*envp)
		envp++;
	while (cmd->arg[i])	
}