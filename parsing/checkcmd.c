/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 00:21:19 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:38:33 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char arg1)
{
	if (arg1 == PIPE)
		return (1);
	return (0);
}

int	check_orand(char arg1, char arg2)
{
	if (arg1 == PIPE && arg2 == PIPE)
		return (OR);
	if (arg1 == AMPERSAND && arg2 == AMPERSAND)
		return (AND);
	return (0);
}

int	check_opt(char meta1, char meta2)
{
	return (meta1 == OPT && ft_isalpha(meta2));
}

int	check_redir(char meta1, char meta2)
{
	if (meta1 == REDIR_IN && meta2 == REDIR_IN)
		return (HEREDOC);
	if (meta1 == REDIR_OUT && meta2 == REDIR_OUT)
		return (APPEND);
	if (meta1 == REDIR_IN)
		return (REDIR_IN);
	if (meta1 == REDIR_OUT)
		return (REDIR_OUT);
	return (0);
}

int	check_arg(char meta1, char meta2)
{
	if (check_orand(meta1, meta2))
		return (check_orand(meta1, meta2));
	else if (check_pipe(meta1))
		return (PIPE);
	else if (check_redir(meta1, meta2))
		return (check_redir(meta1, meta2));
	else if (meta1 == QUOTE)
		return (meta1);
	else if (meta1 == DOUBLE_QUOTE)
		return (DOUBLE_QUOTE);
	return (0);
}
