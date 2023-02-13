/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:03:53 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/09 21:40:26 by npiya-is         ###   ########.fr       */
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

void	sig_handle(int signo, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
