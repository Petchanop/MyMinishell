/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:41:51 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/25 18:52:29 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	return (c < 33);
}

char	*trim_space(char *param)
{
	int	i;

	i = 0;
	while (ft_isspace(param[i]) && param[i] != '\0')
		i++;
	return (&param[i]);
}

char	*trim_character(char *param)
{
	int	i;

	i = 0;
	while (!ft_isspace(param[i]) && param[i])
		i++;
	return (&param[i]);
}

int	find_index(char *param, int meta)
{
	int	i;

	i = 0;
	while (param[i])
	{
		if (check_arg(param[i], param[i + 1]) == meta)
			break ;
		i++;
	}
	if (!param[i])
		return (-1);
	return (i);
}

int	find_nextarg(char *str)
{
	int	i;

	i = 0;
	while (!ft_isspace(str[i]) && str[i])
		i++;
	while (ft_isspace(str[i]) && str[i])
		i++;
	while (!ft_isspace(str[i]) && str[i] && !check_arg(str[i], str[i + 1]))
		i++;
	return (i);
}
