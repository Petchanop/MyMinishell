/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:20:43 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:19:49 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_implement(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (1);
}

char	*ft_getenv(char *str)
{
	int	i;
	int	size;
	int	j;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (NULL);
	size = ft_strlen(str);
	while (g_all.env && g_all.env[i] && ft_strncmp(g_all.env[i], str, size))
		i++;
	if (g_all.env[i])
	{
		while (g_all.env[i] && g_all.env[i][j] != '=')
			j++;
		j++;
		return (&g_all.env[i][j]);
	}
	return (NULL);
}

int	find_envsize(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

char	**copy_env(char **envp)
{
	char	**my_env;
	int		i;
	int		size;

	i = 0;
	my_env = malloc(sizeof(char *) * (find_envsize(envp) + 1));
	while (envp && envp[i])
	{
		size = ft_strlen(envp[i]) + 1;
		my_env[i] = malloc(sizeof(char) * size);
		ft_memcpy(my_env[i], envp[i], size);
		my_env[i][size - 1] = '\0';
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}
