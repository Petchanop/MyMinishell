/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:55:19 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/14 22:25:47 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_cmd(t_cmd *cmd, char **env)
{
	cmd->cmd = malloc(sizeof(char));
	cmd->cmd[0] = '\0';
	cmd->filename = ft_strdup("/tmp/");
	cmd->flag = 0;
	cmd->argv = NULL;
	cmd->next = NULL;
	cmd->env = env;
	cmd->pid = 0;
}

void	shift_cmd(t_cmd *lst_cmd, char **envp)
{
	lst_cmd->next = malloc(sizeof(t_cmd));
	initialize_cmd(lst_cmd->next, envp);
}

t_cmd	*assign_cmd(t_cmd *lst_cmd, t_token *cmd, char **envp)
{
	if (cmd && check_flag(cmd->flag))
	{
		if (!lst_cmd->flag)
			lst_cmd->flag = cmd->flag;
		else
		{
			shift_cmd(lst_cmd, envp);
			lst_cmd = lst_cmd->next;
			lst_cmd->flag = cmd->flag;
		}
		shift_cmd(lst_cmd, envp);
		lst_cmd = lst_cmd->next;
	}
	else
	{
		cmd->token = check_envar(cmd->token);
		lst_cmd->cmd = free_str(lst_cmd->cmd, cmd->token, &ft_strjoin);
		if (cmd->track)
			lst_cmd->cmd = free_str(lst_cmd->cmd, "\a", &ft_strjoin);
		lst_cmd->flag = cmd->flag;
	}
	return (lst_cmd);
}

void	assign_argv(t_cmd *lst, char **env)
{
	while (lst)
	{
		if (!check_flag(lst->flag))
			lst->argv = ft_split(lst->cmd, '\a');
		else
			lst->argv = NULL;
		lst->env = env;
		lst = lst->next;
	}
}
