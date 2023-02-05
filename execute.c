/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:12:18 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/04 17:56:39 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		shift_reappend(&lst_cmd);
		shift_inheredoc(&lst_cmd);
		lst_cmd = lst_cmd->next;
	}
	while (wait(0) != -1 || errno != ECHILD)
		;
	dup2(0, g_all.fds);
	lst_cmd = tmp;
}
