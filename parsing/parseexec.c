/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:29:57 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/16 16:17:16 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parseexec(t_cmd *cmd, char **envp)
{
	int	i;
	int	meta;

	i = 0;
	meta = 0;
	printf("token : %s\nflags %d\n", cmd->token, cmd->flag);
	while (*envp)
		envp++;
	/*write fuction that execute cmd*/
	if (cmd->input != NULL)
	{
		assign_nextcmd(cmd);
		parsing(cmd->input, envp, cmd->right);
	}
	else
		cmd->right = NULL;
	return (NULL);
}
