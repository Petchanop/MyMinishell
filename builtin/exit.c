/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:54:52 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/11 18:38:04 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_implement(char *arg, t_token *token, t_cmd *cmd, char **envp)
{
	if (!arg)
	{
		free(arg);
		free_cmd(token);
		free_split(envp);
		ft_free(cmd);
		write(1, "exit\n", 5);
		exit(0);
	}
	return (1);
}
