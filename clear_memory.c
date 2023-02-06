/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:39:33 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/06 19:16:11 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_cmd *cmd)
{
	t_cmd	*fr;
	int		i;

	while (cmd)
	{
		fr = cmd;
		i = 0;
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
	free(cmd);
}

void	free_cmd(t_token *cmd)
{
	int			i;
	t_token		*tmp;

	i = 0;
	tmp = NULL;
	while (cmd)
	{
		tmp = cmd;
		// write(1, tmp->token, ft_strlen(tmp->token));
		// write(1, "\n", 1);
		cmd = cmd->right;
		free(tmp->token);
		tmp->token = NULL;
		free(tmp);
		tmp = NULL;
	}
	// tmp = NULL;
	free(cmd);
}

char	*free_str(char *a, char *b, char *(*f)(const char *, const char *))
{
	char	*ret;

	ret = f(a, b);
	free(a);
	a = NULL;
	return (ret);
}

// int	main(void)
// {
// 	char *str1 = ft_strdup("test free");
// 	char *str2 = ft_strdup("str2");
// 	char *test = free_var(str1, str2, &ft_strjoin);
// 	printf("test : %s\n", test);
// 	free(test);
// 	return (0);
// }