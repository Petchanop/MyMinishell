/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setshellatt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:29:44 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:38:33 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shellatt(void)
{
	sig_hand_main();
	tcgetattr(STDIN_FILENO, &g_all.term);
	g_all.term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_all.term);
}

void	reset_shellatt(void)
{
	tcgetattr(STDIN_FILENO, &g_all.term);
	g_all.term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_all.term);
}
