/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:28:13 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/15 18:07:23 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_nextcmd(t_cmd *cmd)
{
	cmd->right = malloc(sizeof(t_cmd));
	cmd->right->left = cmd;
}

void	assign_flag(char *param, t_cmd *cmd)
{
	if (cmd->flag == OPT)
		return ;
	else if (cmd->left)
	{
		if (check_arg(param[0], param[1]))
		{
			cmd->flag = check_arg(param[0], param[1]);
			if (cmd->flag == OPT)
				cmd->token = find_token(param + 1, cmd);
		}
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
	while (!ft_isspace(param[i]) && param[i] != '\0')
		i++;
	token = malloc((i + 1) * sizeof(char));
	while (j <= i)
	{
		if (check_arg(param[j], param[j + 1]))
			break ;
		token[j] = param[j];
		j++;
	}
	token[j] = '\0';
	assign_flag(&param[j], cmd);
	if (!token[0])
	{
		while (check_arg(param[j], param[j + 1]) && !ft_isspace(param[j]))
			j++;
	}
	cmd->input = &param[j];
	return (token);
}
