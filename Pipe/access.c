/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:27:40 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/05 23:48:23 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(t_cmd *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while(cmd->env[i])
	{
		if (!ft_strncmp(cmd->env[i], "PATH", 4))
			break ;
		i++;
	}
	path = cmd->env[i];
	return (path);
}

int	assign_pathcmd(t_cmd *cmd, char *command)
{
	char	*path;
	char	*new_command;
	char	**path_split;
	int		i;

	i = 0;
	path = find_path(cmd);
	while (*path != '=')
		path++;
	path++;
	path_split = ft_split(path, ':');
	while (path_split[i])
	{
		new_command = ft_strjoin(path_split[i], "/");
		new_command = ft_strjoin(new_command, command);
		if (access(new_command, F_OK | X_OK) != -1)
		{
			cmd->argv[0] = new_command;
			return (1);
		}
		free(new_command);
		i++;
	}
	return (0);
}