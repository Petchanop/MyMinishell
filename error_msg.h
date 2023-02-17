/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:37:50 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:12:30 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

# define CMD_NOTFOUND ": command not found\n"
# define NMR_REQUIRED ": numeric argument required\n"
# define FILE_NOTFOUND ": No such file or directory\n"
# define TOO_MANY	": too many arguments\n"

int		check_isnum(char *str);
void	check_openerror(t_cmd *cmd);

#endif