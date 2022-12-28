/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:29:12 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/28 21:11:41 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

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
	int		i;
	int		j;
	t_token	*cmd;
	t_token	*cmd1;
	t_cmd	*lst_cmd;
	t_cmd	*lst;

	cwd = NULL;
	cmd = NULL;
	if (argc >= 1)
	{
		while (1)
		{
			cwd = getcwd(argv[1], 0);
			prompt = join(join(CYANBG, cwd), ">");
			prompt = join(prompt, RESET);
			prompt = join(prompt, " ");
			arg = readline(prompt);
			cmd = malloc(sizeof(t_token));
			initilize_token(cmd);
			parsing(arg, envp, cmd);
			cmd1 = cmd;
			// while (cmd1->right)
			// {
			// 	printf("cmd : %s flag : %d track : %d\n", cmd1->token, cmd1->flag, cmd1->track);
			// 	cmd1 = cmd1->right;
			// }
			lst_cmd = malloc(sizeof(t_cmd));
			build_cmd(lst_cmd, cmd, envp);
			assign_argv(lst_cmd, envp);
			j = 0;
			lst = lst_cmd;
			while (lst)
			{
				printf("cmd[%d] : %s\n", j, lst->cmd);
				printf("flag[%d] : %d\n", j, lst->flag);
				i = 0;
				while (lst->argv[i])
				{
					printf("arg : %s\n", lst->argv[i]);
				i++;
				}
				j++;
				lst = lst->next;
			}
			execute_cmd(t_cmd *lst_cmd);
		}
	}
	return (0);
}
