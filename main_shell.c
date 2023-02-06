/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:29:12 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/07 00:13:48 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	print_cmd(t_cmd *lst_cmd)
{
	int		i;
	int		j;
	t_cmd	*lst;

	j = 0;
	lst = lst_cmd;
	while (lst)
	{
		dprintf(2, "cmd[%d] : %s\n", j, lst->cmd);
		dprintf(2, "flag[%d] : %d\n", j, lst->flag);
		i = 0;
		while (lst->argv && lst->argv[i])
		{
			dprintf(2, "argv[%d] : %s\n", j, lst->argv[i]);
			i++;
		}
		j++;
		lst = lst->next;
	}
	lst = NULL;
}

void	sig_handle(int signo, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;

	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
	tmp = cwd;
	free(tmp);
	return (prompt);
}

void	print_token(t_token *cmd)
{
	while (cmd)
	{
		printf("token : %s\n", cmd->token);
		printf("flag   : %d\n", cmd->flag);
		printf("track   : %d\n", cmd->track);
		cmd = cmd->right;
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

int	main(int argc, char **argv, char **envp)
{
	char	*cwd;
	char	*prompt;
	char	*arg;
	// char 	**envp;
	t_token	*cmd;
	t_cmd	*lst_cmd;

	cwd = NULL;
	cmd = NULL;
	// envp = environ;
	if (argc >= 1)
	{
		cwd = getcwd(argv[1], 0);
		prompt = get_current_path(cwd);
		while (1)
		{
			arg = readline(prompt);
			sig_hand_main();
			add_history(arg);
			cmd = malloc(sizeof(t_token));
			initilize_token(cmd);
			parsing(arg, envp, cmd);
			if (cmd->input)
			{
				lst_cmd = malloc(sizeof(t_cmd));
				// print_token(cmd);
				build_cmd(lst_cmd, cmd, envp);
				free_cmd(cmd);
				assign_argv(lst_cmd, envp);
				// print_cmd(lst_cmd);
				execute_cmd(lst_cmd);
				cwd = getcwd(argv[1], 0);
				free(prompt);
				prompt = get_current_path(cwd);
				ft_free(lst_cmd);
				lst_cmd = NULL;
			}
			free(arg);
		}
		free(prompt);
		free(cwd);
		rl_clear_history();
	}
	return (0);
}
