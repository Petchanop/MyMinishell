/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:19:35 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 14:34:58 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_linelen(char *input, t_cmd *cmd)
{
	int	len;

	len = 0;
	if (ft_strlen(cmd->argv[0]) >= ft_strlen(input) - 1)
		len = ft_strlen(cmd->argv[0]);
	else
		len = ft_strlen(input) - 1;
	return (len);
}

void	encrypt_str(t_cmd *cmd)
{
	char	*c;
	int		i;

	i = 0;
	while (cmd->argv[0][i])
	{
		c = ft_itoa(cmd->argv[0][i]);
		cmd->filename = free_str(cmd->filename, c, &ft_strjoin);
		free(c);
		c = NULL;
		i++;
	}
	free(c);
	c = NULL;
}

void	run_heredoc(int rd, t_cmd *cmd, char *read_char, char *input)
{
	int		len;

	len = 0;
	write(1, "<", 1);
	while (rd)
	{
		rd = read(0, read_char, BUFFER_SIZE);
		input = free_str(input, read_char, &ft_strjoin);
		if (read_char[0] == '\n')
		{
			len = find_linelen(input, cmd);
			if (!ft_strncmp(input, cmd->argv[0], len))
			{
				free(input);
				break ;
			}
			else
				ft_putstr_fd(input, g_all.heredoc);
			write(1, "<", 1);
			free(input);
			input = ft_strdup("");
		}
	}
	free(read_char);
}

void	heredoc_implement(t_cmd *cmd)
{
	int		rd;
	char	*read_char;
	char	*input;

	rd = 1;
	input = malloc((BUFFER_SIZE) * sizeof(char));
	read_char = malloc((BUFFER_SIZE + 1) * sizeof(char));
	input[0] = '\0';
	read_char[1] = '\0';
	run_heredoc(rd, cmd, read_char, input);
	close(g_all.heredoc);
}

// int	main(void)
// {
// 	t_cmd *cmd = malloc(sizeof(t_cmd));
// 	char	*arg[] = {"/bin/cat", NULL};

// 	char	*argv[] = {"testheredoc", NULL};
// 	cmd->argv = argv;
// 	cmd->next = NULL;
// 	g_all.filename = "test.tmp";
// 	int	fd = open(g_all.filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
// 	g_all.heredoc = fd;
// 	close(g_all.heredoc);
// 	heredoc_implement(cmd);
// 	dup2(g_all.heredoc, STDIN_FILENO);
// 	close(g_all.heredoc);
// 	execve(arg[0], &arg[1], NULL);
// 	unlink(g_all.filename);
// }
