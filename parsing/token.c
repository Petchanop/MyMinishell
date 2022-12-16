/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:28:13 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/16 16:13:18 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_nextcmd(t_cmd *cmd)
{
	cmd->right = malloc(sizeof(t_cmd));
	cmd->right->left = cmd;
	cmd->right->input = NULL;
	cmd->right->token = NULL;
	cmd->right->right = NULL;
	cmd->right->flag = 0;
}

void	assign_flag(char *param, t_cmd *cmd)
{
	if (cmd->left)
	{
		if (check_arg(param[0], param[1]))
			cmd->flag = check_arg(param[0], param[1]);
		else if (cmd->left->flag == CMD)
			cmd->flag = ARG;
		else
			cmd->flag = CMD;
	}
	else
		cmd->flag = CMD;
}

char	*find_token(char *param, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	j = 0;
	while (!check_arg(param[i], param[i + 1]) && !ft_isspace(param[i]))
		i++;
	assign_flag(param, cmd);
	if (i == 0)
	{
		while (check_arg(param[i], param[i + 1]) && param[i])
			i++;
	}
	token = malloc((i + 1) * sizeof(char));
	while (j < i)
	{
		token[j] = param[j];
		j++;
	}
	token[j] = '\0';
	cmd->input = &param[j];
	return (token);
}
