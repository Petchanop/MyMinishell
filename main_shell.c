/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:29:12 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/12 23:43:19 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

t_global	g_all;

void	print_split(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		dprintf(2, "argv[%d] : %s\n", i, argv[i]);
		i++;
	}
}

void	print_cmd(t_cmd *lst_cmd)
{
	int		j;
	t_cmd	*lst;

	j = 0;
	lst = lst_cmd;
	while (lst)
	{
		dprintf(2, "cmd[%d] : %s\n", j, lst->cmd);
		dprintf(2, "flag[%d] : %d\n", j, lst->flag);
		print_split(lst->argv);
		j++;
		lst = lst->next;
	}
	lst = NULL;
}

char	*get_current_path(char *cwd)
{
	char	*prompt;
	char	*tmp;

	tmp = ft_strjoin(CYANBG, cwd);
	prompt = ft_strjoin(tmp, ">");
	free(tmp);
	tmp = prompt;
	prompt = ft_strjoin(prompt, RESET);
	free(tmp);
	tmp = prompt;
	prompt = ft_strjoin(prompt, " ");
	free(tmp);
	tmp = NULL;
	return (prompt);
}

void	print_token(t_token *cmd)
{
	while (cmd)
	{
		printf("t_token : %p\n", cmd);
		printf("token : %s\n", cmd->token);
		printf("flag   : %d\n", cmd->flag);
		printf("track   : %d\n", cmd->track);
		cmd = cmd->right;
	}
	printf("last : %p\n", cmd);
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
	t_cmd	*lst_cmd;

	(void)argv;
	cmd = NULL;
	g_all.env = copy_env(envp);
	if (argc >= 1)
	{
		while (1)
		{
			g_all.cwd = ft_getenv("PWD");
			g_all.prompt = get_current_path(g_all.cwd);
			sig_hand_main();
			g_all.arg = readline(g_all.prompt);
			cmd = malloc(sizeof(t_token));
			add_history(g_all.arg);
			initilize_token(cmd);
			parsing(g_all.arg, g_all.env, cmd);
			if (cmd && cmd->input)
			{
				lst_cmd = malloc(sizeof(t_cmd));
				build_cmd(lst_cmd, cmd, g_all.env);
				assign_argv(lst_cmd, g_all.env);
				free_cmd(cmd);
				execute_cmd(lst_cmd);
				ft_free(lst_cmd);
				lst_cmd = NULL;
			}
			free(g_all.prompt);
		}
		rl_clear_history();
	}
	return (0);
}
