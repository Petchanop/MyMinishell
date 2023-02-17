/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:30:45 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:38:33 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cd(t_cmd *cmd)
{
	if (!cmd->argv[1])
	{
		if (chdir(getenv("HOME")) == -1)
		{
			perror("Path not found");
			exit(1);
		}
	}
	else if (!ft_strncmp(cmd->argv[1], "-", ft_strlen(cmd->argv[1])))
	{
		if (ft_getenv("OLDPWD"))
			chdir(ft_getenv("OLDPWD"));
	}
	else if (chdir(cmd->argv[1]) == -1)
	{
		perror("Path not found");
		exit(1);
	}
	return (1);
}

void	add_oldpwd(char *oldpwd)
{
	int		index;

	index = 0;
	if (find_env("OLDPWD"))
	{
		index = find_envindex("OLDPWD");
		free(g_all.env[index]);
		g_all.env[index] = ft_strdup(oldpwd);
	}
	else
		change_env(oldpwd);
	free(oldpwd);
}

int	cd_implement(t_cmd *cmd)
{
	int		index;
	char	*pwd;
	char	*old_pwd;

	index = 0;
	pwd = getcwd(NULL, MAXPATHLEN);
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	if (execute_cd(cmd))
		add_oldpwd(old_pwd);
	free(pwd);
	pwd = getcwd(NULL, MAXPATHLEN);
	index = find_envindex("PWD");
	free(g_all.env[index]);
	g_all.env[index] = ft_strjoin("PWD=", pwd);
	free(pwd);
	return (1);
}
