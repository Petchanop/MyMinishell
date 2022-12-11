/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:41:51 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/10 16:28:45 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	return (c < 33);
}

char	*find_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (NULL);
	while (ft_isspace(arg[i]) && arg[i] != '\0')
		i++;
	while (!ft_isspace(arg[i]) && arg[i] != '\0')
		i++;
	return (&arg[i]);
}
