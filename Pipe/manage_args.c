/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:16:22 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/23 22:36:58 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	argv_len(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

char	**argv_join(char **arg1, char **arg2)
{
	int		len1;
	int		len2;
	int		i;
	char	**new_argv;

	i = 0;
	len1 = argv_len(arg1);
	len2 = argv_len(arg2);
	new_argv = malloc((len1 + len2 + 1) * sizeof(char *));
	while (*arg1)
	{
		new_argv[i] = *arg1++;
		i++;
	}
	while (*arg2)
	{
		new_argv[i] = *arg2++;
		i++;
	}
	new_argv[i] = NULL;
	return (new_argv);
}

void	remove_cmd(t_cmd **cmd, t_cmd *rem)
{
	t_cmd	*re;
	int		i;

	i = 0;
	re = *cmd;
	if (*cmd == NULL)
		return ;
	if ((*cmd) == rem)
	{
		// dprintf(2, "cmd->argv : %s\n", (*cmd)->argv[0]);
		*cmd = (*cmd)->next;
		// while (re->argv[i])
		// {
		// 	free(re->argv[i]);
		// 	i++;
		// }
		// free(re->argv);
		// free(re->cmd);
		free(re);
	}
	else
		remove_cmd(&(*cmd)->next, rem);
}

void	shift_arg(t_cmd **cmd, int flag)
{
	t_cmd	*head;

	head = (*cmd);
	while ((*cmd)->next && (*cmd)->next->flag == flag)
	{
		(*cmd) = (*cmd)->next->next;
	}
}