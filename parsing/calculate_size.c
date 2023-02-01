/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:00:07 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/31 22:27:23 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

char	*copy_meta(char	*param)
{
	int		i;
	int		j;
	int		k;
	int		sign;
	char	*copy;

	j = 0;
	k = 0;

	sign = find_meta(param);
	i = size_argquote(param, sign);
	copy = malloc((i) * sizeof(char));
	while (j < i)
	{
		if (param[j] != sign)
		{
			copy[k] = param[j];
			k++;
		}
		j++;
	}
	copy[k] = '\0';
	return (copy);
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