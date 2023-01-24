/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:24:25 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/24 21:30:39 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*assign_token(char *param, t_token *cmd, int i)
{
	int		j;
	char	*token;

	j = 0;
	token = malloc((i + 1) * sizeof(char));
	while (j < i)
	{
		token[j] = param[j];
		j++;
	}
	token[j] = '\0';
	if (j > 1 && (token[0] == QUOTE || token[0] == DOUBLE_QUOTE))
	{
		if (token[j - 1] == QUOTE || token[j - 1] == DOUBLE_QUOTE)
		{
			cmd->flag = ARG;
			cmd->track = 0;
		}
	}
	cmd->input = &param[j];
	return (token);
}
