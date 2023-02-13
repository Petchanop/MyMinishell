/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:12:18 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/13 18:07:09 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_cmd *lst_cmd)
{
	t_cmd	*tmp;
	t_cmd	*cpy;
	int		status;

	g_all.fds = dup(0);
	tmp = lst_cmd;
	cpy = lst_cmd;
	while (lst_cmd)
	{
		if (lst_cmd && lst_cmd->flag != PIPE)
		{
			// print_cmd(lst_cmd);
			execute(lst_cmd);
		}
		g_all.redir = count_redir(lst_cmd);
		lst_cmd = shift_redir(lst_cmd, g_all.redir);
		// dprintf(2, "redir : %d\n", g_all.redir);
		if (lst_cmd && lst_cmd->argv && !ft_strncmp(lst_cmd->argv[0], "exit", 5)
			&& (!lst_cmd->next || (lst_cmd->next && lst_cmd->next->flag != PIPE)))
		{
			write(1, "exit\n", 5);
			ft_free(tmp);
			free_split(g_all.env);
			exit(0);
		}
		if (lst_cmd)
			lst_cmd = lst_cmd->next;
	}
	while (cpy)
	{
		waitpid(cpy->pid, &status, 0);
		cpy = cpy->next;
	}
	dup2(0, g_all.fds);
	close(g_all.fds);
	lst_cmd = tmp;
}
