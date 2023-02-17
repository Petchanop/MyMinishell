/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:39:33 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:19:31 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(t_cmd *cmd)
{
	t_cmd	*fr;

	while (cmd)
	{
		fr = cmd;
		cmd = cmd->next;
		free_split(fr->argv);
		fr->argv = NULL;
		free(fr->cmd);
		fr->cmd = NULL;
		if (fr->filename[0])
			unlink(fr->filename);
		free(fr->filename);
		free(fr);
	}
	fr = NULL;
	free(cmd);
	cmd = NULL;
}

void	free_cmd(t_token *cmd)
{
	t_token		*tmp;

	tmp = NULL;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->right;
		free(tmp->token);
		tmp->token = NULL;
		free(tmp);
		tmp = NULL;
	}
	free(cmd);
	cmd = NULL;
}

char	*free_str(char *a, char *b, char *(*f)(const char *, const char *))
{
	char	*ret;

	if (!b && a)
		return (a);
	else if (!a && b)
		return (b);
	ret = f(a, b);
	free(a);
	a = NULL;
	return (ret);
}

void	free_split(char **spl)
{
	int	i;

	i = 0;
	while (spl && spl[i])
	{
		free(spl[i]);
		spl[i] = NULL;
		i++;
	}
	free(spl);
	spl = NULL;
}

void	free_lstcmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	free(tmp->cmd);
	free_split(tmp->argv);
	tmp->cmd = NULL;
	free(tmp);
	tmp = NULL;
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