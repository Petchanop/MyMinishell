/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:01:05 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/03 01:14:35 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkin_quote(char *param, int pos)
{
	if (find_index(param, QUOTE) < pos && find_index(&param[pos], QUOTE) > pos)
		return (1);
	if (find_index(param, DOUBLE_QUOTE) < pos
		&& find_index(&param[pos], DOUBLE_QUOTE) > pos)
		return (1);
	return (0);
}

int	check_ifredir(char *param)
{
	if (find_index(param, REDIR_IN) >= 0)
		return (find_index(param, REDIR_IN));
	if (find_index(param, REDIR_OUT) >= 0)
		return (find_index(param, REDIR_OUT));
	if (find_index(param, APPEND) >= 0)
		return (find_index(param, APPEND));
	if (find_index(param, HEREDOC) >= 0)
		return (find_index(param, HEREDOC));
	return (-1);
}

void	gettoken(char *param, t_token *cmd)
{
	if (*param == '\0')
		return ;
	if (cmd->left && cmd->left->track != 1)
		cmd->input = trim_space(param);
	if (ft_isspace(param[0]) && cmd->left)
		cmd->left->track = 1;
	cmd->token = find_token(cmd->input, cmd);
}

void	parsing(char *arg, char **envp, t_token *cmd)
{
	if (!*arg)
		return ;
	cmd->input = arg;
	gettoken(arg, cmd);
	build_token(cmd, envp);
}
