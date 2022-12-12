/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:28:13 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/12 19:45:03 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_nextcmd(t_cmd *cmd)
{
	cmd->right = malloc(sizeof(t_cmd));
	cmd->right->left = cmd;
}

int	find_token(char *param, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (!ft_isspace(param[i]) && param[i] != '\0' && !cmd->token)
	{
		cmd->token = check_arg(param[i], param[i + 1]);
		i++;
	}
	return (i);
}
