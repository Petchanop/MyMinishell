/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:27:40 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/09 23:27:12 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(t_cmd *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (cmd->env && cmd->env[i])
	{
		if (!ft_strncmp(cmd->env[i], "PATH", 4))
			break ;
		i++;
	}
	path = cmd->env[i];
	shift_path(path);
	return (path);
}

void	shift_path(char *path)
{
	while (*path != '=')
		path++;
	path++;
}

int	assign_pathcmd(t_cmd *cmd, char *command)
{
	char	*path;
	char	*new_command;
	char	**path_split;
	int		i;

	i = 0;
	if (!command || !command[0])
		return (0);
	if (access(cmd->argv[0], F_OK | X_OK) != -1)
		return (1);
	path = find_path(cmd);
	path_split = ft_split(path, ':');
	while (path_split[i])
	{
		new_command = ft_strjoin(path_split[i], "/");
		new_command = free_str(new_command, command, &ft_strjoin);
		if (access(new_command, F_OK | X_OK) != -1)
		{
			cmd->argv[0] = new_command;
			return (1);
		}
		free(new_command);
		i++;
	}
	free_split(path_split);
	return (0);
}
