/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:00:07 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/09 18:14:46 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

char	*copy_meta(char	*param, int sign)
{
	int		i;
	int		j;
	int		k;
	char	*copy;

	j = 0;
	k = 0;
	i = size_argquote(param, sign) + 1;
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
	free(param);
	return (copy);
}

static	char	*getenv_str(char *token, int start, size_t len)
{
	char	*en_var;
	char	*var;

	en_var = ft_substr(token, start, len);
	var = ft_getenv(en_var);
	free(en_var);
	en_var = NULL;
	return (var);
}

char	*copy_envar(char *token, int sign, int size)
{
	int		idx;
	int		j;
	int		k;
	char	*copy;
	char	*en_var;

	j = 0;
	k = 0;
	copy = malloc((ft_strlen(token) + size + 1) * sizeof(char));
	while (token[j])
	{
		if (token[j] && token[j] == EN_VAR)
		{
			idx = envar_len(&token[j + 1]);
			en_var = getenv_str(token, j + 1, idx);
			ft_memcpy(&copy[k], en_var, ft_strlen(en_var));
			k += ft_strlen(en_var);
			j += idx;
		}
		else if (token[j] && token[j] != sign)
			copy[k++] = token[j];
		j++;
	}
	copy[k] = '\0';
	return (copy);
}

/*int	main(void)
{
	char *token = "for test$tentnarin";
	char *en_var = "envar";
	int sign = DOUBLE_QUOTE;
	char *ret = copy_envar(token, en_var, sign);
	printf("%s\n", ret);
}*/

//gcc -Wall -Werror -Wextra -o var parsing/calculate_size.c expand/expander.c  expand/en_var.c parsing/parsing_utils.c parsing/checkcmd.c -L libft -lft