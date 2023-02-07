/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:00:07 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/07 17:00:57 by npiya-is         ###   ########.fr       */
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

char	*copy_envar(char *token, int sign, int size)
{
	int		i;
	int		j;
	int		k;
	int		var_idx;
	char	*copy;
	char	*en_var;

	j = 0;
	k = 0;
	i = ft_strlen(token);
	copy = malloc((i + size + 1) * sizeof(char));
	while (token[j])
	{
		if (token[j] && token[j] == EN_VAR)
		{
			var_idx = envar_len(&token[j + 1]);
			en_var = ft_substr(token, j + 1, var_idx);
			if (getenv(en_var))
				en_var = getenv(en_var);
			else
				en_var = ft_strdup("");
			while (*en_var)
				copy[k++] = *en_var++;
			j += var_idx;
			free(en_var);
			en_var = NULL;
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