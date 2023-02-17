/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:10:11 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/14 15:26:48 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"
# include "../shell_types.h"

int		find_meta(char *param);
int		check_meta(char meta);
int		size_argquote(char *param, int sign);
int		envar_size(char *token);
int		envartoken_size(char *token);
int		envar_len(char *token);
int		find_quoteindex(char *token, char sign);
int		find_envars(char *token);
char	*check_envar(char *token);

#endif