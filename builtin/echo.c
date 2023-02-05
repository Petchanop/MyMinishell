/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:54:38 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/04 15:39:48 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_implement(t_cmd *cmd)
{
	char	**argv;
	int		i;
	int		nl;

	i = 1;
	nl = 0;
	argv = cmd->argv;
	if (argv_len(argv) > 1)
	{
		while (argv[i] && ft_strncmp(argv[i], "-n", 3) == 0)
		{
			nl = 1;
			i++;
		}
		while (argv[i])
		{
			printf("%s", argv[i]);
			if (argv[i + 1] && argv[i][0] != '\0')
				printf(" ");
			i++;
		}
	}
	if (nl == 0)
		printf("\n");
	return (1);
}
