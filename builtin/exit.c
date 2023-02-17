/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:54:52 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 17:13:06 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_implement(char *arg, t_token *token, t_cmd *cmd, char **envp)
{
	free(arg);
	free_cmd(token);
	if (cmd && cmd->argv && cmd->argv[1] && check_isnum(cmd->argv[1]))
		g_all.status = ft_atoi(cmd->argv[1]);
	write(1, "exit\n", 5);
	if (cmd && cmd->argv && cmd->argv[1] && !check_isnum(cmd->argv[1]))
		access_error(cmd, NMR_REQUIRED);
	else if (cmd && cmd->argv[1] && cmd->argv[2])
	{
		access_error(cmd, TOO_MANY);
		return (1);
	}
	free_split(envp);
	ft_free(cmd);
	if (g_all.filename)
		free(g_all.filename);
	exit(g_all.status);
	return (1);
}
