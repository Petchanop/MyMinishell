/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmeta.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:12:27 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/19 17: by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_meta(char meta)
{
	if (meta == QUOTE)
		return (QUOTE);
	else if (meta == DOUBLE_QUOTE)
		return (DOUBLE_QUOTE);
	return (0);
}

char	*split_quote(char *param)
{
	int		size;
	int		i;
	char	*str_quote;

	size = 0;
	i = 0;
	while (!check_meta(param[size]) && param[size])
		size++;
	if (param[size] != check_meta(param[size]))
		return (NULL);
	str_quote = malloc((size + 1) * sizeof(char));
	while (!check_meta(param[i]) && param[i])
	{
		str_quote[i] = param[i];
		i++;
	}
	str_quote[i] = '\0';
	return (str_quote);
}
