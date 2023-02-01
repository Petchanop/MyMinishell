/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:29:57 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/19 20:3 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_flag(int flag)
{
	if (flag == PIPE || flag == REDIR_IN || flag == REDIR_OUT
		|| flag == AMPERSAND || flag == APPEND || flag == OR)
		return (1);
	return (0);
}

char	*copy_noquote(char *param, int index)
{
	char	*temp;
	int		i;

	i = 0;
	temp = malloc((index + 1) * sizeof(char));
	while (i < index)
	{
		temp[i] = param[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

void	build_token(t_token *cmd, char **envp)
{
	if (cmd->input[0] != '\0')
	{
		assign_nexttoken(cmd);
		parsing(cmd->input, envp, cmd->right);
	}
	else
		cmd->right = NULL;
}

t_cmd	*build_cmd(t_cmd *lst_cmd, t_token *cmd, char **envp)
{
	t_token	*tmp;
	t_cmd	*ret;

	initialize_cmd(lst_cmd, envp);
	ret = lst_cmd;
	while (cmd)
	{
		if (cmd->flag == DOUBLE_QUOTE || cmd->flag == QUOTE)
			cmd->track = 1;
		lst_cmd = assign_cmd(lst_cmd, cmd, envp);
		tmp = cmd;
		cmd = cmd->right;
		if (cmd && (cmd->flag == DOUBLE_QUOTE || cmd->flag == QUOTE))
			cmd->track = 0;
		else if (cmd && (cmd->left->track == 1))
			cmd->track = 1;
		free(tmp->token);
		free(tmp);
	}
	return (ret);
}
