/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:55:19 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/24 23:46:35 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


