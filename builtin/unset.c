/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:55:59 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/10 23:11:13 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	arrange_newenv(char **env, int index)
{
	while (env[index + 1])
	{
		env[index] = env[index + 1];
		index++;
	}
	env[index] = NULL;
}

int	unset_implement(t_cmd *cmd)
{
	int		i;
	int		env_len;

	i = 1;
	env_len = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (find_env(cmd->argv[i]))
		{
			env_len = find_envindex(cmd->argv[i]);
			free(g_all.env[env_len]);
			arrange_newenv(g_all.env, env_len);
		}
		i++;
	}
	return (1);
}
