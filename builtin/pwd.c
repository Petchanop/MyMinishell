/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:02:56 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:38:33 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_implement(void)
{
	char	*pwd;

	pwd = getcwd(NULL, MAXPATHLEN);
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}
