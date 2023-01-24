/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:01:05 by npiya-is          #+#    #+#             */
/*   Updated: 2023/01/20 23:48:33 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkin_quote(char *param, int pos)
{
	if (find_index(param, QUOTE) < pos && find_index(&param[pos], QUOTE) > pos)
		return (1);
	if (find_index(param, DOUBLE_QUOTE) < pos
		&& find_index(&param[pos], DOUBLE_QUOTE) > pos)
		return (1);
	return (0);
}

int	check_ifredir(char *param)
{
	if (find_index(param, REDIR_IN) >= 0)
		return (find_index(param, REDIR_IN));
	if (find_index(param, REDIR_OUT) >= 0)
		return (find_index(param, REDIR_OUT));
	if (find_index(param, APPEND) >= 0)
		return (find_index(param, APPEND));
	if (find_index(param, HEREDOC) >= 0)
		return (find_index(param, HEREDOC));
	return (-1);
}

char	*arrange_cmd(char *param)
{
	int	meta;
	int	arg;
	int	next_arg;

	meta = check_ifredir(param);
	arg = check_arg(param[meta], param[meta + 1]);
	printf("\nparam : %s\nmeta : %d\narg : %d\n", &param[meta], meta, arg);
	if (meta >= 0 && !checkin_quote(param, meta))
	{
		if (arg == REDIR_OUT || arg == APPEND)
		{
			next_arg = find_nextarg(&param[meta]);
			while (ft_isspace(param[meta + next_arg]) && param[meta + next_arg])
				meta++;
			if (check_arg(param[meta + next_arg], param[meta + next_arg + 1]))
				return (param);
			printf("next arg : %s\n", &param[meta + next_arg]);
		}
		return (param);
	}
	else
		return (param);
}

void	gettoken(char *param, t_token *cmd)
{
	if (*param == '\0')
		return ;
	if (cmd->left && cmd->left->track != 1)
		cmd->input = trim_space(param);
	cmd->token = find_token(cmd->input, cmd);
}

void	parsing(char *arg, char **envp, t_token *cmd)
{
	if (!*arg)
		return ;
	cmd->input = arg;
	gettoken(arg, cmd);
	build_token(cmd, envp);
}

void	assign_argv(t_cmd *lst, char **envp)
{
	int	size;

	size = 0;
	while (lst)
	{
		size = calculate_size(lst->cmd);
		lst->argv = create_argv(lst->cmd, size);
		lst->env = envp;
		lst = lst->next;
	}
}
