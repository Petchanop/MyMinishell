/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:08:42 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/06 21:07:21 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin_parent(t_cmd *cmd)
{
	if (cmd && cmd->argv != NULL && !ft_strncmp(cmd->argv[0], "cd", 3))
		return (cd_implement(cmd));
	return (0);
}

int	is_builtin_child(t_cmd *cmd)
{
	if (cmd && cmd->argv != NULL && !ft_strncmp(cmd->argv[0], "echo", 5))
		return (echo_implement(cmd));
	if (cmd && cmd->argv != NULL && !ft_strncmp(cmd->argv[0], "exit", 5))
		return (1);
	return (0);
}
