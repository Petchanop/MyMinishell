/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:41:51 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/12 20:03:30 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	return (c < 33);
}

int	trim_space(char *param)
{
	int	i;

	i = 0;
	while (ft_isspace(param[i]) && param[i] != '\0')
		i++;
	return (i);
}

char	*find_arg(char *param, t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;
	char	*arg;

	if (param == NULL)
		return (NULL);
	k = 0;
	i = trim_space(param);
	j = find_token(&param[i], cmd);
	arg = malloc((j + 1) * sizeof(char));
	while (!ft_isspace(param[i]) && j && param[i])
	{
		arg[k] = param[i];
		j--;
		i++;
		k++;
	}
	arg[k] = '\0';
	return (arg);
}
