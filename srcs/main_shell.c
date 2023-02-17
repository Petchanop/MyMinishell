/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:29:12 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:19:57 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

t_global	g_all;

char	*read_arg(void)
{
	char	buff[100];
	char	*arg;
	char	*tmp;

	getcwd(buff, 99);
	tmp = ft_strjoin(CYAN, buff);
	g_all.prompt = ft_strjoin(tmp, BLUE" >> "WHITE);
	free(tmp);
	arg = readline(g_all.prompt);
	free(g_all.prompt);
	g_all.prompt = NULL;
	if (arg && arg[0])
		add_history(arg);
	g_all.arg = arg;
	return (arg);
}

void	initilize_token(t_token *cmd)
{
	cmd->left = NULL;
	cmd->right = NULL;
	cmd->input = NULL;
	cmd->token = NULL;
	cmd->flag = 0;
	cmd->track = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*cmd;
	char	*arg;

	(void)argv;
	cmd = NULL;
	g_all.env = copy_env(envp);
	if (argc >= 1)
	{
		set_shellatt();
		rl_catch_signals = 0;
		g_all.pid = 0;
		while (1)
		{
			arg = read_arg();
			cmd = malloc(sizeof(t_token));
			initilize_token(cmd);
			parsing(arg, g_all.env, cmd);
			run_process(cmd);
		}
		reset_shellatt();
		rl_clear_history();
	}
	return (0);
}
