/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:16:22 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/11 12:34:23 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	argv_len(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
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
		new_argv[i] = ft_strdup(*arg1++);
		i++;
	}
	while (*arg2)
	{
		new_argv[i] = ft_strdup(*arg2++);
		i++;
	}
	new_argv[i] = NULL;
	return (new_argv);
}

void	remove_cmd(t_cmd **cmd, t_cmd *rem)
{
	if (*cmd == NULL)
		return ;
	if ((*cmd) == rem)
	{
		*cmd = (*cmd)->next;
		free_lstcmd(rem);
		return ;
	}
	else
		remove_cmd(&(*cmd)->next, rem);
}

void	shift_arg(t_cmd **cmd, int flag)
{
	while ((*cmd)->next && (*cmd)->next->flag == flag)
		(*cmd) = (*cmd)->next->next;
}
