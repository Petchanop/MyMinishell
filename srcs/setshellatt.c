/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setshellatt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:29:44 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/18 02:18:03 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shellatt(void)
{
	tcgetattr(STDIN_FILENO, &g_all.term);
	tcgetattr(STDIN_FILENO, &g_all.shell);
	g_all.term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_all.term);
}

void	reset_shellatt(void)
{
	g_all.shell.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_all.shell);
}
