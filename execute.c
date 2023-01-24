/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:12:18 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/24 23:54:54 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_cmd *lst_cmd)
{
	fds = dup(0);
	// print_cmd(lst_cmd);
	while (lst_cmd)
	{
		execute(lst_cmd);
		if (lst_cmd->next && lst_cmd->next->flag == PIPE)
			lst_cmd = lst_cmd->next;
		shift_reappend(&lst_cmd);
		shift_inheredoc(lst_cmd);
		lst_cmd = lst_cmd->next;
	}
	while (wait(0) != -1 || errno != ECHILD)
		;
	dup2(0, fds);
	return (0);
}
