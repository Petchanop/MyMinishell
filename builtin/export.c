/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:48:53 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/10 22:58:59 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_env(char *env)
{
	int	i;
	int	size;

	i = 0;
	if (!env || !env[0])
		return (NULL);
	size = ft_strlen(env);
	while (g_all.env && g_all.env[i] && ft_strncmp(g_all.env[i], env, size))
		i++;
	return (g_all.env[i]);
}

int	find_envindex(char *env)
{
	int	i;
	int	size;

	i = 0;
	if (!env || !env[0])
		return (-1);
	size = ft_strlen(env);
	while (g_all.env && g_all.env[i] && ft_strncmp(g_all.env[i], env, size))
		i++;
	if (!g_all.env[i])
		return (-1);
	return (i);
}

void	change_env(char *argv)
{
	char	**env;
	char	**tmp;
	char	**tmp1;

	env = malloc(sizeof(char *) * 2);
	env[0] = malloc(sizeof(char) * ft_strlen(argv) + 1);
	ft_memcpy(env[0], argv, ft_strlen(argv));
	env[0][ft_strlen(argv)] = '\0';
	env[1] = NULL;
	tmp = env;
	tmp1 = g_all.env;
	g_all.env = argv_join(g_all.env, env);
	free_split(tmp);
	free_split(tmp1);
}

int	export_implement(t_cmd *cmd)
{
	char	*path;
	int		env_len;
	int		i;

	i = 1;
	while (cmd->argv && cmd->argv[i])
	{
		env_len = envar_len(cmd->argv[i]);
		path = ft_substr(cmd->argv[i], 0, envar_len(cmd->argv[i]));
		if (find_env(path))
		{
			env_len = find_envindex(path);
			free(g_all.env[env_len]);
			g_all.env[env_len] = ft_strdup(cmd->argv[i]);
		}
		else
			change_env(cmd->argv[i]);
		free(path);
		i++;
	}
	return (1);
}

//export niinoi=Rati may=LuLL