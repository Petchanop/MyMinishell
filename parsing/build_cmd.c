/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:55:19 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/25 18:50:58 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_cmd(t_cmd *cmd, char **env)
{
	cmd->cmd = malloc(sizeof(char));
	cmd->cmd[0] = '\0';
	cmd->flag = 0;
	cmd->next = NULL;
	cmd->env = env;
}

char	*build_quotecmd(t_token *cmd, char *argv)
{
	if (cmd != NULL)
	{
		if (!check_flag(cmd->flag))
			argv = join(argv, cmd->token);
		return (argv);
	}
	else
		return (NULL);
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
		lst_cmd->cmd = ft_strjoin(lst_cmd->cmd, cmd->token);
		lst_cmd->flag = cmd->flag;
		if (cmd->right && (cmd->flag != OPT && cmd->flag != DOUBLE_QUOTE))
			lst_cmd->cmd = ft_strjoin(lst_cmd->cmd, " ");
	}
	return (lst_cmd);
}

void	assign_argv(t_cmd *lst, char **envp)
{
	int	size;

	size = 0;
	while (lst)
	{
		size = calculate_size(lst->cmd);
		lst->argv = create_argv(lst->cmd, size);
		lst->env = envp;
		lst = lst->next;
	}
}
