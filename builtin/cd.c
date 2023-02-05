/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:30:45 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/04 15:31:00 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_implement(t_cmd *cmd)
{
	if (chdir(cmd->argv[1]) == -1)
	{
		perror("Path not found");
		exit(1);
	}
	return (1);
}
