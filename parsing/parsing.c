/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:01:05 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/12 19:14:23 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	gettoken(char *param, t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	if (*param == '\0')
		return ;
	i = trim_space(param);
	j = find_token(&param[i], cmd);
	cmd->cmd = malloc((j + 1) * sizeof(char));
	while (!ft_isspace(param[i]) && j && param[i])
	{
		cmd->cmd[k] = param[i];
		j--;
		i++;
		k++;
	}
	cmd->cmd[k] = '\0';
	cmd->input = &param[i];
	cmd->arg = find_arg(cmd->input, cmd);
}

int	parsing(char *arg, char **envp, t_cmd *cmd)
{
	if (!*arg)
		return (0);
	cmd->input = arg;
	gettoken(cmd->input, cmd);
	if (!cmd->arg)
		return (0);
	cmd->result = parseexec(cmd, envp);
	return (0);
}
