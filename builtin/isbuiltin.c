/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:08:42 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/29 22:41:02 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_implement(t_cmd *cmd)
{
	if (chdir(cmd->argv[1]) == -1)
	{
		perror("Path not found");
		exit(1);
	}
	return (1);
}

int	is_builtin(t_cmd *cmd)
{
	if (cmd && cmd->argv != NULL && !ft_strncmp(cmd->argv[0], "cd", 3))
		return (cd_implement(cmd));
	return (0);
}