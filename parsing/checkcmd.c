/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 00:21:19 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/12 18:40:04 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe(char arg)
{
	return (arg == PIPE);
}

int	check_orcmd(char arg1, char arg2)
{
	if (arg1 == PIPE && arg2 == PIPE)
		return (PIPE);
	return (0);
}

int	check_arg(char meta1, char meta2)
{
	int	i;

	i = 0;
	if (check_pipe(meta1))
		return (meta1);
	else if (check_orcmd(meta1, meta2))
		return (meta1 + meta2);
	return (0);
}
