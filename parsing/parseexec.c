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

void	initialize_cmd(t_cmd *cmd, char **env)
{
	cmd->cmd = malloc(sizeof(char));
	cmd->cmd[0] = '\0';
	cmd->flag = 0;
	cmd->next = NULL;
	cmd->env = env;
}

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

int	find_meta(char *param)
{
	int	i;

	i = 0;
	while (!check_meta(param[i]) && param[i])
		i++;
	if (!param[i])
		return (-1);
	return (i);
}

void	build_token(t_token *cmd, char **envp)
{
	if (cmd->input != NULL)
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
	while (cmd->right)
	{
		if (check_flag(cmd->flag))
		{
			if (!lst_cmd->flag)
				lst_cmd->flag = cmd->flag;
			else
			{
				lst_cmd->next = malloc(sizeof(t_cmd));
				initialize_cmd(lst_cmd->next, envp);
				lst_cmd = lst_cmd->next;
				lst_cmd->flag = cmd->flag;
			}
			lst_cmd->next = malloc(sizeof(t_cmd));
			initialize_cmd(lst_cmd->next, envp);
			lst_cmd = lst_cmd->next;
		}
		else
		{
			lst_cmd->cmd = ft_strjoin(lst_cmd->cmd, cmd->token);
			lst_cmd->flag = cmd->flag;
			if (cmd->right && (cmd->flag != OPT && cmd->flag != DOUBLE_QUOTE))
				lst_cmd->cmd = ft_strjoin(lst_cmd->cmd, " ");
		}
		tmp = cmd;
		cmd = cmd->right;
		free(tmp->token);
		free(tmp);
	}
	free(cmd);
	return (ret);
}
