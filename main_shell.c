/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:29:12 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/08 15:21:39 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

char	*join(const char *s1, const char *s2)
{
	char	*result;

	result = malloc(strlen(s1) + strlen(s2) + 1);
	if (result)
	{
		strcpy(result, s1);
		strcat(result, s2);
	}
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cwd;
	char	*prompt;
	char	*cmd;

	cwd = NULL;
	if (argc >= 1)
	{
		cwd = getcwd(argv[1], 0);
		prompt = join(join(CYANBG, cwd), ">");
		prompt = join(prompt, RESET);
		prompt = join(prompt, " ");
		cmd = readline(prompt);
		parsing(cmd, envp);
	}
	return (0);
}
