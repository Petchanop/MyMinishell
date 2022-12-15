/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:01:05 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/15 17:49:31 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	gettoken(char *param, t_cmd *cmd)
{
	if (*param == '\0')
		return ;
	cmd->input = trim_space(param);
	cmd->token = find_token(cmd->input, cmd);
	// printf("token : %s\nflags %d\n", cmd->token, cmd->flag);
	// printf("input : %s\n", cmd->input);
}

int	parsing(char *arg, char **envp, t_cmd *cmd)
{
	if (!*arg)
		return (0);
	cmd->input = arg;
	gettoken(cmd->input, cmd);
	// if (!cmd->arg)
	// 	return (0);
	parseexec(cmd, envp);
	return (0);
}
