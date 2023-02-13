/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:47:42 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/13 18:21:37 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_flagredir(int flag)
{
	if (flag == REDIR_IN || flag == REDIR_OUT || flag == APPEND)
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

int	opendup_mode(t_cmd *cmd, int flag)
{
	int	fd;

	fd = 0;
	if (cmd->argv)
	{
		if (flag == REDIR_OUT)
		{
			fd = open(cmd->argv[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			dup2(fd, STDOUT_FILENO);
		}
		else if (flag == APPEND)
		{
			fd = open(cmd->argv[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
			dup2(fd, STDOUT_FILENO);
		}
		else if (flag == REDIR_IN)
		{
			fd = open(cmd->argv[0], O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		close(fd);
	}
	if (fd < 0)
	{
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, ": No such file or directory\n", 29);
		dup2(0, fd);
		exit(1);
	}
	return (fd);
}

int	redir(t_cmd *cmd)
{
	int		times;
	// int		fd;
	t_cmd	*tmp;

	// fd = 0;
	times = 0;
	tmp = cmd;
	if (cmd && (cmd)->next && (check_flagredir(cmd->flag)
			|| check_flagredir(cmd->next->flag)))
	{
		if (check_flagredir(cmd->next->flag))
			cmd = cmd->next;
		else
			tmp = tmp->next;
		while (cmd && cmd->next)
		{
			if (check_flagredir(cmd->flag) && cmd->next)
			{
				g_all.fd = opendup_mode(cmd->next, cmd->flag);
				if (argv_len((cmd)->next->argv) > 1 && cmd->next != tmp)
					tmp->argv = argv_join(tmp->argv, &(cmd)->next->argv[1]);
				cmd = cmd->next->next;
				times += 2;
			}
			else
				break ;
		}
		dup2(0, g_all.fd);
	}
	dprintf(2, "fd : %d\n", g_all.fd);
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
			if (check_flagredir(cmd->flag) && cmd->next)
			{
				cmd = cmd->next->next;
				times += 2;
			}
			else
				cmd = cmd->next;
		}
	}
	return (times);
}
