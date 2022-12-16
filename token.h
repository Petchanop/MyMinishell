/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:20:19 by npiya-is          #+#    #+#             */
/*   Updated: 2022/12/16 15:40:48 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

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

#endif
