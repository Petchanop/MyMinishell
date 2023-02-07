/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:12:18 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/07 16:22:08 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_all;

void	execute_cmd(t_cmd *lst_cmd)
{
	t_cmd *tmp;

	g_all.fds = dup(0);
	tmp = lst_cmd;
	while (lst_cmd)
	{
		execute(lst_cmd);
		if (lst_cmd->next && lst_cmd->next->flag == PIPE)
			lst_cmd = lst_cmd->next;
		if (lst_cmd->argv && !ft_strncmp(lst_cmd->argv[0], "exit", 5)
			&& (!lst_cmd->next || (lst_cmd->next && lst_cmd->next->flag != PIPE)))
		{
			write(1, "exit\n", 5);
			ft_free(lst_cmd);
			exit(0);
		}
		shift_reappend(&lst_cmd);
		shift_inheredoc(&lst_cmd);
		lst_cmd = lst_cmd->next;
	}
	while (wait(0) != -1 || errno != ECHILD)
		;
	dup2(0, g_all.fds);
	lst_cmd = tmp;
}
