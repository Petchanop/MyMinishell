/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:01:53 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/14 15:26:59 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"
# include "../shell_types.h"

int		is_builtin_parent(t_cmd *cmd);
int		is_builtin_child(t_cmd *cmd);
int		cd_implement(t_cmd *cmd);
int		echo_implement(t_cmd *cmd);
int		export_implement(t_cmd *cmd);
int		env_implement(char **env);
int		unset_implement(t_cmd *cmd);
int		pwd_implement(void);
int		exit_implement(char *arg, t_token *token, t_cmd *cmd, char **envp);

#endif