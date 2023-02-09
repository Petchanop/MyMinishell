/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:00:00 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/03 15:3 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_argquote(char *param, int sign)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (param[j] && !ft_isspace(param[j]))
	{
		if (sign == DOUBLE_QUOTE)
		{
			if (param[j] != sign && param[j] != EN_VAR)
				i++;
		}
		else if (sign == QUOTE)
		{
			if (param[j] != sign)
				i++;
		}
		else
			i++;
		j++;
	}
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
	if (!param)
		return (-1);
	while (!check_meta(param[i]) && param[i] && !ft_isspace(param[i]))
		i++;
	if (!param[i])
		return (-1);
	return (check_meta(param[i]));
}

char	*check_envar(char *token)
{
	int		var_idx;
	int		sign;

	var_idx = find_envars(token);
	sign = find_meta(token);
	if (var_idx < 0 && (sign == QUOTE || sign == DOUBLE_QUOTE))
		return (copy_meta(token, sign));
	if (sign == QUOTE)
		return (copy_meta(token, sign));
	var_idx = envar_size(token);
	token = copy_envar(token, sign, var_idx);
	return (token);
}
