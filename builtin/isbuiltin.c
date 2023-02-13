/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:08:42 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/11 17:07:03 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin_parent(t_cmd *cmd)
{
	if (cmd && cmd->argv != NULL && !ft_strncmp(cmd->argv[0], "cd", 3))
		return (cd_implement(cmd));
	if (cmd && cmd->argv != NULL && !ft_strncmp(cmd->argv[0], "export", 7))
		return (export_implement(cmd));
	if (cmd && cmd->argv != NULL && !ft_strncmp(cmd->argv[0], "env", 4))
		return (env_implement(g_all.env));
	if (cmd && cmd->argv != NULL && !ft_strncmp(cmd->argv[0], "unset", 6))
		return (unset_implement(cmd));
	if (cmd && cmd->argv != NULL && !cmd->argv[1]
		&& !ft_strncmp(cmd->argv[0], "exit", 5))
		return (exit_implement(NULL, NULL, cmd, g_all.env));
	if (cmd && cmd->argv != NULL && !ft_strncmp(cmd->argv[0], "pwd", 4))
		return (pwd_implement());
	return (0);
}

int	is_builtin_child(t_cmd *cmd)
{
	if (cmd && cmd->argv != NULL && !ft_strncmp(cmd->argv[0], "echo", 5))
		return (echo_implement(cmd));
	return (0);
}
