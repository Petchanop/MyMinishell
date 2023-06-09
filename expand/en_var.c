/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   en_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 00:46:05 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/18 16:35:05 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_envars(char *token)
{
	int	i;

	i = 0;
	while (token && token[i])
	{
		if (token[i] == EN_VAR)
			return (i);
		i++;
	}
	return (-1);
}

int	find_quoteindex(char *token, char sign)
{
	int	i;

	i = 0;
	while (token && token[i])
	{
		if (token[i] == sign)
			return (i);
		i++;
	}
	return (-1);
}

int	envar_len(char *token)
{
	int	i;

	i = 0;
	if (token[0] == '?' && !ft_isalnum(token[1]))
		return (1);
	while (ft_isalnum(token[i]) && token[i])
		i++;
	return (i);
}

int	envartoken_size(char *token)
{
	int	i;
	int	j;
	int	size;

	j = 0;
	size = 0;
	while (token[j])
	{
		if (token[j] == EN_VAR)
		{
			j++;
			i = 0;
			while (ft_isalnum(token[j + i]) && token[j + i])
				i++;
			size += i;
			j += i;
		}
		j++;
	}
	return (size);
}

int	envar_size(char *token)
{
	char	*geten;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = 0;
	while (token && token[j])
	{
		if (token[j] == EN_VAR)
		{
			j++;
			i = envar_len(&token[j]);
			geten = getenv_str(token, j, i);
			if (geten)
				size += ft_strlen(geten);
			j += i;
			continue ;
		}
		else
			j++;
	}
	return (size);
}
