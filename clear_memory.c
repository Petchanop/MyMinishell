/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:39:33 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/09 18:03:03 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, int size)
{
	unsigned char	*new_ptr;

	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return ((void *)new_ptr);
}

void	ft_free(t_cmd *cmd)
{
	t_cmd	*fr;
	int		i;

	while (cmd)
	{
		fr = cmd;
		cmd = cmd->next;
		i = 0;
		while (fr->argv && fr->argv[i])
		{
			free(fr->argv[i]);
			fr->argv[i] = NULL;
			i++;
		}
		free(fr->argv);
		fr->argv = NULL;
		free(fr->cmd);
		fr->cmd = NULL;
		free(fr);
	}
	free(cmd);
	cmd = NULL;
}

void	free_cmd(t_token *cmd)
{
	t_token		*tmp;

	tmp = NULL;
	// print_token(cmd);
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

	ret = f(a, b);
	free(a);
	a = NULL;
	return (ret);
}

void	free_split(char **spl)
{
	int	i;

	i = 0;
	while (spl[i])
	{
		free(spl[i]);
		spl[i] = NULL;
		i++;
	}
	free(spl);
	spl = NULL;
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