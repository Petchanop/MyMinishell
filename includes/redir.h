/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:35:24 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:44:23 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# define BUFFER_SIZE 1 

# include "shell_types.h"

int		open_in(t_cmd *cmd, int flag);
int		open_out(t_cmd *cmd, int flag);
int		open_redirin(t_cmd *cmd, int flag);
int		opendup_mode(t_cmd *cmd, int flag);
int		check_flagredir(int flag);
int		count_redir(t_cmd *cmd);
int		redir(t_cmd *cmd);
int		argv_len(char **arg);
int		assign_pathcmd(t_cmd *cmd, char *command);
void	run_heredoc(int rd, t_cmd *cmd, char *read_char, char *input);
void	heredoc_implement(t_cmd *cmd);
void	openerror(t_cmd	*cmd, int fd);
void	pipe_cmd(t_cmd *cmd, int *pipefd);
void	close_fd(t_cmd *cmd, int *pipefd);
void	remove_cmd(t_cmd **cmd, t_cmd *rem);
void	shift_arg(t_cmd **cmd, int flag);
void	openerror(t_cmd	*cmd, int fd);
void	shift_path(char *path);
void	encrypt_str(t_cmd *cmd);
char	*find_path(t_cmd *cmd);
char	**argv_join(char **arg1, char **arg2);
t_cmd	*shift_redir(t_cmd *cmd, int times);

#endif