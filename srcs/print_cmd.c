/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:07:12 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:19:45 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_split(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		dprintf(2, "argv[%d] : %s\n", i, argv[i]);
		i++;
	}
}

void	print_cmd(t_cmd *lst_cmd)
{
	int		j;
	t_cmd	*lst;

	j = 0;
	lst = lst_cmd;
	while (lst)
	{
		dprintf(2, "cmd[%d] : %s\n", j, lst->cmd);
		dprintf(2, "flag[%d] : %d\n", j, lst->flag);
		print_split(lst->argv);
		j++;
		lst = lst->next;
	}
	lst = NULL;
}

void	print_token(t_token *cmd)
{
	while (cmd)
	{
		printf("t_token : %p\n", cmd);
		printf("token : %s\n", cmd->token);
		printf("flag   : %d\n", cmd->flag);
		printf("track   : %d\n", cmd->track);
		cmd = cmd->right;
	}
	printf("last : %p\n", cmd);
}
