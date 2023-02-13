/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:28:13 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/09 21:53:29 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_tokensize(char *param, t_token *cmd)
{
	int	i;
	int	sign;

	i = 0;
	sign = cmd->flag;
	if (!param || !param[0])
		return (i);
	if (cmd->left && (cmd->track < 0 || cmd->left->track < 0))
	{
		i++;
		while (param[i] && sign != check_arg(param[i], param[i + 1]))
			i++;
		i++;
	}
	else
	{
		while (param[i] && !check_arg(param[i], param[i + 1]) && !ft_isspace(param[i]))
			i++;
		if (param[i])
			sign = check_arg(param[i], param[i + 1]);
		if (sign == DOUBLE_QUOTE || sign == QUOTE)
		{
			i++;
			while (param[i] && sign != check_arg(param[i], param[i + 1]))
				i++;
			i++;
		}
	}
	return (i);
}

void	assign_track(int arg, t_token *cmd)
{
	if (cmd->left->track == -1)
		cmd->track = -1;
	else if (cmd->left->track == -2)
		cmd->track = -2;
	else if (arg == QUOTE)
		cmd->track = -1;
	else if (arg == DOUBLE_QUOTE)
		cmd->track = -2;
}

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

void	track_quote(int arg, t_token *cmd)
{
	if (arg == QUOTE && cmd->left->track == -1)
	{
		cmd->flag = arg;
		cmd->track = 0;
	}
	else if (arg == DOUBLE_QUOTE && cmd->left->track == -2)
	{
		cmd->flag = arg;
		cmd->track = 0;
	}
	else
	{
		cmd->flag = cmd->left->flag;
		cmd->track = cmd->left->track;
	}
}

void	assign_flag(char *param, t_token *cmd)
{
	int	arg;

	arg = check_arg(param[0], param[1]);
	if (cmd && cmd->left)
	{
		if (cmd->left->track < 0)
			track_quote(arg, cmd);
		else if (arg)
		{
			cmd->flag = arg;
			assign_track(arg, cmd);
		}
		else if (cmd->left->flag == CMD || cmd->left->flag == ARG
			|| cmd->left->flag == QUOTE || cmd->left->flag == DOUBLE_QUOTE)
				cmd->flag = ARG;
		else
			cmd->flag = CMD;
	}
	else
	{
		if (arg)
			cmd->flag = arg;
		else
			cmd->flag = CMD;
	}
}

char	*find_token(char *param, t_token *cmd)
{
	int		i;
	char	*token;

	if (!param)
		return (NULL);
	i = 0;
	assign_flag(param, cmd);
	if (cmd != NULL && cmd->input && cmd->input[0])
		i = count_tokensize(param, cmd);
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
