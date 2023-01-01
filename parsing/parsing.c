/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:01:05 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/30 22:19:51 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	gettoken(char *param, t_token *cmd)
{
	if (*param == '\0')
		return ;
	if (cmd->left && cmd->left->track != 1)
		cmd->input = trim_space(param);
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

void	assign_argv(t_cmd *lst, char **envp)
{
	int	size;

	size = 0;
	while (lst)
	{
		size = calculate_size(lst->cmd);
		lst->argv = create_argv(lst->cmd, size);
		lst->env = envp;
		lst = lst->next;
	}
}
