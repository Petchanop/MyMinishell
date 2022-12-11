/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:28:13 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/10 16:29:01 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_token(char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	arg = cmd;
	while (cmd[i])
	{
		if (cmd[i] == PIPE)
		if (cmd[i] == REDIR_IN)
		if (cmd[i] == REDIR_OUT)
		if (cmd[i] == AMPERSAND)
		if (cmd[i] == QUOTE)
		if (cmd[i] == DOUBLE_QUOTE)
		if (cmd[i] == O_PAREN)
		if (cmd[i] == C_PAREN)
		if (cmd[i] == WILDCARD)

		i++;
	}
}
