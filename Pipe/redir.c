/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:47:42 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 20:34:14 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_flagredir(int flag)
{
	if (flag == REDIR_IN || flag == REDIR_OUT
		|| flag == APPEND || flag == HEREDOC)
		return (flag);
	return (0);
}

t_cmd	*shift_redir(t_cmd *cmd, int times)
{
	int	i;

	i = 0;
	while (i < times && cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (cmd);
}

int	check_openfile(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		times;

	times = 0;
	tmp = cmd;
	if (check_flagredir(cmd->next->flag))
		cmd = cmd->next;
	else
		tmp = tmp->next;
	while (cmd && cmd->next)
	{
		if (check_flagredir(cmd->flag) && cmd->next)
		{
			cmd->fd = opendup_mode(cmd->next, cmd->flag);
			if (argv_len((cmd)->next->argv) > 1
				&& cmd->next != tmp)
				tmp->argv = argv_join(tmp->argv, &(cmd)->next->argv[1]);
			cmd = cmd->next->next;
			times += 2;
		}
		else
			break ;
	}
	return (times);
}

int	redir(t_cmd *cmd)
{
	int		times;

	times = 0;
	if (cmd && (cmd)->next && (check_flagredir(cmd->flag)
			|| check_flagredir(cmd->next->flag)))
		times = check_openfile(cmd);
	return (times);
}

int	count_redir(t_cmd *cmd)
{
	int		times;
	int		flag;

	times = 0;
	if (cmd && (cmd)->next && (check_flagredir(cmd->flag)
			|| check_flagredir(cmd->next->flag)))
	{
		if (check_flagredir(cmd->next->flag))
			cmd = cmd->next;
		while (cmd && cmd->next)
		{
			flag = check_flagredir(cmd->flag);
			if (flag == HEREDOC && cmd->next)
				encrypt_str(cmd->next);
			if (check_flagredir(cmd->flag) && cmd->next)
			{
				cmd = cmd->next->next;
				times += 2;
			}
			else
				break ;
		}
	}
	return (times);
}
