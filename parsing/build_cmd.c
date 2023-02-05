/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:55:19 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/04 17:24:12 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_cmd(t_cmd *cmd, char **env)
{
	cmd->cmd = malloc(sizeof(char));
	cmd->cmd[0] = '\0';
	cmd->flag = 0;
	cmd->argv = malloc(sizeof(char *));
	cmd->argv[0] = NULL;
	cmd->next = NULL;
	cmd->env = env;
}

t_cmd	*assign_cmd(t_cmd *lst_cmd, t_token *cmd, char **envp)
{
	if (check_flag(cmd->flag))
	{
		if (!lst_cmd->flag)
			lst_cmd->flag = cmd->flag;
		else
		{
			lst_cmd->next = malloc(sizeof(t_cmd));
			initialize_cmd(lst_cmd->next, envp);
			lst_cmd = lst_cmd->next;
			lst_cmd->flag = cmd->flag;
		}
		lst_cmd->next = malloc(sizeof(t_cmd));
		initialize_cmd(lst_cmd->next, envp);
		lst_cmd = lst_cmd->next;
	}
	else
	{
		cmd->token = check_envar(cmd->token);
		if (cmd->track)
		{
			lst_cmd->cmd = free_str(lst_cmd->cmd, cmd->token, &ft_strjoin);
			lst_cmd->cmd = free_str(lst_cmd->cmd, "\a", &ft_strjoin);
		}
		else
			lst_cmd->cmd = free_str(lst_cmd->cmd, cmd->token, &ft_strjoin);
		lst_cmd->flag = cmd->flag;
	}
	return (lst_cmd);
}

void	assign_argv(t_cmd *lst, char **envp)
{
	while (lst)
	{
		lst->argv = ft_split(lst->cmd, '\a');
		lst->env = envp;
		lst = lst->next;
	}
}
