/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:21:15 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:20:08 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_isnum(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] && !ft_isdigit(str[i]))
		i++;
	if (!str[i])
		return (0);
	return (1);
}

void	access_error(t_cmd *cmd, char *error)
{
	ft_putstr_fd("Mybash: ", 1);
	ft_putstr_fd(cmd->argv[0], 1);
	if (cmd->argv[1])
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
	}
	ft_putstr_fd(error, 2);
}

void	openerror(t_cmd	*cmd, int fd)
{
	if (fd < 0)
	{
		access_error(cmd, FILE_NOTFOUND);
		exit(1);
	}
}

void	check_openerror(t_cmd *cmd)
{
	while (cmd)
	{
		if (check_flagredir(cmd->flag) && cmd->next)
			openerror(cmd->next, cmd->fd);
		cmd = cmd->next;
	}
}
