/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:28:13 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/24 21:30:26 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_nexttoken(t_token *cmd)
{
	cmd->right = malloc(sizeof(t_token));
	cmd->right->left = cmd;
	cmd->right->input = NULL;
	cmd->right->token = NULL;
	cmd->right->right = NULL;
	cmd->right->track = 0;
	cmd->right->flag = 0;
}

void	track_quote(char *param, t_token *cmd)
{
	if (check_arg(param[0], param[1]) == QUOTE
		|| check_arg(param[0], param[1]) == DOUBLE_QUOTE)
	{
		cmd->flag = check_arg(param[0], param[1]);
		cmd->track = 0;
	}
	else
	{
		cmd->flag = cmd->left->flag;
		cmd->track = 1;
	}
}

void	assign_flag(char *param, t_token *cmd)
{
	if (cmd->left)
	{
		if (cmd->left->track == 1)
			track_quote(param, cmd);
		else if (check_arg(param[0], param[1]))
		{
			cmd->flag = check_arg(param[0], param[1]);
			if (check_arg(param[0], param[1]) == QUOTE
				|| check_arg(param[0], param[1]) == DOUBLE_QUOTE)
				cmd->track = -1;
		}
		else if (cmd->left->flag == CMD || cmd->left->flag == ARG
			|| cmd->left->flag == QUOTE || cmd->left->flag == DOUBLE_QUOTE)
				cmd->flag = ARG;
		else
			cmd->flag = CMD;
	}
	else
	{
		if (check_arg(param[0], param[1]))
			cmd->flag = check_arg(param[0], param[1]);
		else
			cmd->flag = CMD;
	}
}

char	*find_token(char *param, t_token *cmd)
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
		if (check_arg(param[i], param[i + 1]) == AND
			|| check_arg(param[i], param[i + 1]) == OR
			|| check_arg(param[i], param[i + 1]) == APPEND
			|| check_arg(param[i], param[i + 1]) == HEREDOC)
			i++;
		i++;
	}
	token = assign_token(param, cmd, i);
	return (token);
}
