/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:00:00 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/02 01:26:23 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_argquote(char *param, int sign)
{
	int		i;

	i = 1;
	while (param[i] != sign && param[i])
		i++;
	i++;
	while (!ft_isspace(param[i]) && param[i])
		i++;
	return (i);
}

int	check_meta(char meta)
{
	if (meta == QUOTE)
		return (QUOTE);
	else if (meta == DOUBLE_QUOTE)
		return (DOUBLE_QUOTE);
	return (0);
}

int	find_meta(char *param)
{
	int	i;

	i = 0;
	while (!check_meta(param[i]) && param[i] && !ft_isspace(param[i]))
		i++;
	if (!param[i])
		return (-1);
	return (check_meta(param[i]));
}

char	*check_envar(char *token, char **envp)
{
	char	*en_var;
	int		var_idx;
	int		dquote_idx;
	int		quote_idx;
	int		i;
	int		j;

	var_idx = find_envars(token);
	dquote_idx = find_dquoteindex(token);
	quote_idx = find_quoteindex(token);
	printf("D : %d , Q : %d\n", dquote_idx, quote_idx);
	if (quote_idx < dquote_idx
		|| (!token[quote_idx] && !token[dquote_idx]) || !token[var_idx])
		return (token);
	var_idx++;
	en_var = ft_substr(token, var_idx, envar_len(&token[var_idx]));
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], en_var, ft_strlen(en_var)))
			break ;
		i++;
	}
	free(en_var);
	if (!envp[i])
		return (ft_strdup(""));
	j = 0;
	while (envp[i][j] && envp[i][j] != '=')
		j++;
	j++;
	if (envp[i][j])
	{
		en_var = ft_strdup(&envp[i][j]);
		// int k = 0;
		// en_var = malloc(sizeof(char) * (j + 1));
		// while (envp[i][j])
		// {
		// 	en_var[k] = envp[i][j];
		// 	k++;
		// 	j++;
		// }
		// en_var[k] = '\0';
		free(token);
	}
	return (en_var);
}