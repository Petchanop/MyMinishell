/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:29:57 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/12 19:43:59 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parseexec(t_cmd *cmd, char **envp)
{
	int	i;
	int	meta;

	i = 0;
	meta = 0;
	printf("cmd : %s\narg : %s\ntoken: %d\n", cmd->cmd, cmd->arg, cmd->token);
	printf("input : %s\n", cmd->input);
	while (*envp)
		envp++;
	/*write fuction that exxcute cmd*/
	if (cmd->input != NULL)
	{
		assign_nextcmd(cmd);
		parsing(cmd->input, envp, cmd->right);
	}
	return (NULL);
}
