/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:24:25 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/09 22:21:58 by npiya-is         ###   ########.fr       */
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
