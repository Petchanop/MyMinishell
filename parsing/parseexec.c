/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:29:57 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/12 00:21:40 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parseexec(t_cmd *cmd, char **envp)
{
	int	i;

	i = 0;
	printf("cmd : %s\narg : %s\n", cmd->cmd, cmd->arg);
	while (*envp)
		envp++;
	while (cmd->arg[i])
	{
		if (cmd->arg[i] == PIPE)
		if (cmd->arg[i] == REDIR_IN)
		if (cmd->arg[i] == REDIR_OUT)
		if (cmd->arg[i] == AMPERSAND)
		i++;
	}
	return (NULL);
}
