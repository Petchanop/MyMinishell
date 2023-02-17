/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:20:19 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/14 15:27:46 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "shell_types.h"

# define OPTION '-'
# define PIPE '|'
# define REDIR_IN '<'
# define REDIR_OUT '>'
# define QUOTE '\''
# define DOUBLE_QUOTE '"'
# define EN_VAR '$'
# define AMPERSAND '&'
# define O_PAREN '('
# define C_PAREN ')'
# define WILDCARD '*'
# define OPT '-' 
# define CMD 1
# define ARG 2
# define AND 76
# define APPEND 200
# define HEREDOC 201 
# define OR 248
# define FILE 300

void	assign_flag(char *param, t_token *cmd);
int		copy_toenvar(char *en_var, char *copy, int k);
int		count_size(char *param, int i, int sign);
int		count_tokensize(char *str, t_token *cmd);
char	*find_token(char *param, t_token *cmd);
char	*copy_meta(char	*param, int sign);
char	*getenv_str(char *token, int start, size_t len);
char	*copy_envar(char *token, char *copy, int sign);
char	*assign_token(char *param, t_token *cmd, int i);

#endif
