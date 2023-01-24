/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:29:12 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/22 22:10:45 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	print_token(t_token *cmd)
{
	while (cmd)
	{
		printf("token : %s\n", cmd->token);
		// printf("input : %s\n", cmd->input);
		printf("flag   : %d\n", cmd->flag);
		cmd = cmd->right;
	}
}

void	ft_free(t_cmd *cmd)
{
	t_cmd	*fr;
	while (cmd)
	{
		fr = cmd;
		int	i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
		free(cmd->cmd);
		cmd = cmd->next;
		free(fr);
	}
}

void	initilize_token(t_token *cmd)
{
	cmd->left = NULL;
	cmd->input = NULL;
	cmd->token = NULL;
	cmd->flag = 0;
	cmd->track = 0;
}

char	*join(const char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL)
		len1 = 0;
	else
		len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
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
	t_token	*cmd;
	t_cmd	*lst_cmd;

	cwd = NULL;
	cmd = NULL;
	if (argc >= 1)
	{
		cwd = getcwd(argv[1], 0);
		prompt = join(join(CYANBG, cwd), ">");
		prompt = join(prompt, RESET);
		prompt = join(prompt, " ");
		while (1)
		{
			arg = readline(prompt);
			add_history(arg);
			cmd = malloc(sizeof(t_token));
			initilize_token(cmd);
			parsing(arg, envp, cmd);
			lst_cmd = malloc(sizeof(t_cmd));
			build_cmd(lst_cmd, cmd, envp);
			assign_argv(lst_cmd, envp);
			execute_cmd(lst_cmd);
			free(arg);
			ft_free(lst_cmd);
		}
	}
	return (0);
}
