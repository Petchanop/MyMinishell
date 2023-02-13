/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:30:45 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/11 18:33:28 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_oldpwd(void)
{
	char	*pwd;
	char	*old_pwd;
	int		index;

	index = 0;
	pwd = getcwd(NULL, MAXPATHLEN);
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	if (find_env("OLDPWD"))
	{
		index = find_envindex("OLDPWD");
		free(g_all.env[index]);
		g_all.env[index] = ft_strdup(old_pwd);
	}
	else
		change_env(old_pwd);
	free(old_pwd);
	free(pwd);
}

int	cd_implement(t_cmd *cmd)
{
	int		index;
	char	*pwd;

	index = 0;
	add_oldpwd();
	if (chdir(cmd->argv[1]) == -1)
	{
		perror("Path not found");
		exit(1);
	}
	pwd = getcwd(NULL, MAXPATHLEN);
	index = find_envindex("PWD");
	free(g_all.env[index]);
	g_all.env[index] = ft_strjoin("PWD=", pwd);
	free(pwd);
	return (1);
}
