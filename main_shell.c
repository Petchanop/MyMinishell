/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:29:12 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/12 18:38:30 by npiya-is         ###   ########.fr       */
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
	char	*arg;
	t_cmd	*cmd;

	cwd = NULL;
	if (argc >= 1)
	{
		cwd = getcwd(argv[1], 0);
		prompt = join(join(CYANBG, cwd), ">");
		prompt = join(prompt, RESET);
		prompt = join(prompt, " ");
		arg = readline(prompt);
		cmd = malloc(sizeof(t_cmd));
		cmd->token = 0;
		parsing(arg, envp, cmd);
	}
	return (0);
}
