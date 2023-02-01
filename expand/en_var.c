/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   en_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 00:46:05 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/02 01:20:51 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_envars(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == EN_VAR)
			break ;
		i++;
	}
	return (i);
}

int	find_dquoteindex(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == DOUBLE_QUOTE)
			break ;
		i++;
	}
	return (i);
}

int	find_quoteindex(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == QUOTE)
			break ;
		i++;
	}
	return (i);
}

int	envar_len(char *token)
{
	int	i;

	i = 0;
	while (ft_isalnum(token[i]) && token[i])
		i++;
	return (i);
}
