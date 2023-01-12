/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:12:18 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/12 23:05:04 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_cmd *lst_cmd)
{
	fds = dup(0);
	while (lst_cmd)
	{
		execute(lst_cmd);
		if (lst_cmd->next && lst_cmd->next->flag == PIPE)
			lst_cmd = lst_cmd->next;
		if (lst_cmd->next && (lst_cmd->next->flag == REDIR_OUT || lst_cmd->next->flag == APPEND))
			lst_cmd = lst_cmd->next->next;
		lst_cmd = lst_cmd->next;
		//print_cmd(lst_cmd);
	}
	while (wait(0) != -1 || errno != ECHILD)
		;
	dup2(0, fds);
	return (0);
}
