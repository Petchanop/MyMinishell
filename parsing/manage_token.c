/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:24:25 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/13 21:25:49 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*assign_token(char *param, t_token *cmd, int i)
{
	int		j;
	char	*token;

	j = 0;
	if (!param || !param[0] || i == 0)
		return (NULL);
	token = malloc((i + 1) * sizeof(char));
	while (j < i)
	{
		token[j] = param[j];
		j++;
	}
	token[j] = '\0';
	if (token[0] == cmd->flag)
	{
		i = 1;
		while (token[i] != cmd->flag && token[i])
			i++;
		if (param[i] == cmd->flag)
			cmd->track = 0;
	}
	cmd->input = &param[j];
	return (token);
}

int	count_size(char *param, int i, int sign)
{
	i++;
	while (param[i] && sign != check_arg(param[i], param[i + 1]))
		i++;
	i++;
	return (i);
}

int	count_tokensize(char *str, t_token *cmd)
{
	int	i;
	int	sign;

	i = 0;
	sign = cmd->flag;
	if (!str || !str[0])
		return (i);
	if (cmd->left && (cmd->track < 0 || cmd->left->track < 0))
		i = count_size(str, i, sign);
	else
	{
		while (str[i] && !check_arg(str[i], str[i + 1]) && !ft_isspace(str[i]))
			i++;
		if (str[i])
			sign = check_arg(str[i], str[i + 1]);
		if (sign == DOUBLE_QUOTE || sign == QUOTE)
			i = count_size(str, i, sign);
	}
	return (i);
}
