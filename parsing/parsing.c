/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:01:05 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/10 17:07:59 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*gettoken(char *param)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	j = 0;
	if (*param == '\0')
		return (0);
	while (ft_isspace(param[i]) && param[i] != '\0')
		i++;
	while (!ft_isspace(param[i + j]) && param[i] != '\0')
		j++;
	cmd = malloc(j * sizeof(char));
	j = 0;
	while (!ft_isspace(param[i]) && param[i])
	{
		cmd[j] = param[i];
		j++;
		i++;
	}
	cmd[j] = '\0';
	return (cmd);
}

int	parsing(char *arg, char **envp, t_cmd *cmd)
{
	int		i;
	char	*next_arg;

	i = 0;
	if (!*arg)
		return (0);
	cmd->cmd = gettoken(arg);
	next_arg = find_arg(arg);
	if (!next_arg)
		return (0);
	cmd->arg = gettoken(next_arg);
	next_arg = find_arg(next_arg);
	cmd->result = parseexec(cmd, envp);
	if (next_arg)
	{
		cmd->right = malloc(sizeof(t_cmd));
		cmd->right->left = cmd;
		parsing(next_arg, envp, cmd->right);
	}
	return (0);
}
