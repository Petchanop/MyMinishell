/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:12:18 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:52:43 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_process(t_cmd *cmd)
{
	while (cmd)
	{
		waitpid(cmd->pid, &g_all.status, 0);
		if (g_all.status == 256)
			g_all.status = 1;
		else if (g_all.status == 2)
			g_all.status = 130;
		else if (g_all.status == 512)
			g_all.status = 127;
		g_all.pid = cmd->pid;
		cmd = cmd->next;
	}
	if (g_all.status == 130)
		ft_putstr_fd("\n", 2);
	dup2(0, g_all.fds);
}

void	execute_cmd(t_cmd *lst_cmd)
{
	t_cmd	*tmp;

	g_all.fds = dup(0);
	tmp = lst_cmd;
	while (lst_cmd)
	{
		if (lst_cmd && lst_cmd->flag != PIPE)
			execute(lst_cmd);
		g_all.redir = count_redir(lst_cmd);
		lst_cmd = shift_redir(lst_cmd, g_all.redir);
		if (lst_cmd && lst_cmd->argv != NULL
			&& !ft_strncmp(lst_cmd->argv[0], "exit", 5))
			lst_cmd = lst_cmd->next;
		if (lst_cmd)
			lst_cmd = lst_cmd->next;
	}
	wait_process(tmp);
	lst_cmd = tmp;
}

void	run_process(t_token *cmd)
{
	t_cmd	*lst_cmd;

	lst_cmd = NULL;
	if (cmd && cmd->input && cmd->token && cmd->token[0])
	{
		lst_cmd = malloc(sizeof(t_cmd));
		build_cmd(lst_cmd, cmd, g_all.env);
		assign_argv(lst_cmd, g_all.env);
		free_cmd(cmd);
		execute_cmd(lst_cmd);
		ft_free(lst_cmd);
		lst_cmd = NULL;
	}
}
