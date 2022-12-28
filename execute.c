/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:12:18 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/28 21:14:46 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_cmd *lst_cmd)
{
	if (lst_cmd->next)
	{
		if (lst_cmd->next->flag == PIPE)
			execute_pipe(lst_cmd);
	}
	else
		execute(lst_cmd);
	return (0);
}