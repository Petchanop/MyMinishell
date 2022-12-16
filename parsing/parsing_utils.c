/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:41:51 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/16 16:07:39 by npiya-is         ###   ########.fr       */
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
