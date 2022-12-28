/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:00:07 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/28 22:52:48 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

int	calculate_size(char *param)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (!param)
		return (0);
	while (param[i])
	{
		while (ft_isspace(param[i]) && param[i])
			i++;
		while (!ft_isspace(param[i]) && param[i] && !check_meta(param[i]))
			i++;
		size++;
		if (check_meta(param[i]))
		{
			i++;
			while (!check_meta(param[i]) && param[i])
				i++;
			i++;
			size++;
		}
	}
	return (size);
}

char	*copy_meta(char	*param)
{
	int		i;
	int		j;
	char	*copy;

	i = 1;
	j = 0;
	while (!check_meta(param[i]) && param[i])
		i++;
	i++;
	copy = malloc((i + 1) * sizeof(char));
	while (j < i)
	{
		copy[j] = param[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

int	find_arglen(char *param)
{
	int	len;

	len = 0;
	if (!check_meta(param[len]))
	{
		while (!ft_isspace(param[len]) && param[len] && !check_meta(param[len]))
			len++;
	}
	else
	{
		len++;
		while (!check_meta(param[len]) && param[len])
			len++;
		len++;
	}
	return (len);
}

char	*copy_arg(char *param, int len)
{
	char	*copy;
	int		i;

	i = 0;
	copy = malloc((len + 1) * sizeof(char));
	while (!ft_isspace(param[i]) && param[i] && !check_meta(param[i]))
	{
		copy[i] = param[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	**create_argv(char *param, int size)
{	
	char	**argv;
	int		i;
	int		len;

	argv = malloc((size + 1) * sizeof(char *));
	len = 0;
	i = 0;
	if (!param)
	{
		argv[0] = NULL;
		return (argv);
	}
	while (param[len])
	{
		param = trim_space(&param[len]);
		if (!param[len])
			break ;
		len = find_arglen(param);
		if (!check_meta(param[len - 1]))
			argv[i] = copy_arg(param, len);
		else if (check_meta(param[len - 1]))
			argv[i] = copy_meta(param);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
/*
int	main(void)
{
	char	**split = NULL;
	int		size = 0;
	int		i = 0;
	//char	*str = "test1 \"test2 test3 \" test4 test5 \"test6 \t\"";
	char	*str1 = "test1 test2test3 \"test4 test5 test6\t\"";

	size = calculate_size(str1);
	printf("size : %d\n", size);
	split = create_argv(str1, size);
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}*/