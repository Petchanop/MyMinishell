/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:03:53 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/06 23:15:56 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_hand_main(void)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;

	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_flags = SA_RESTART;
	sigemptyset(&sig_quit.sa_mask);
	sigaction(SIGQUIT, &sig_quit, NULL);
	sig_int.sa_sigaction = sig_handle;
	sig_int.sa_flags = SA_SIGINFO;
	sigemptyset(&sig_int.sa_mask);
	sigaction(SIGINT, &sig_int, NULL);
}