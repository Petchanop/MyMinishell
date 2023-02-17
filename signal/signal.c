/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:03:53 by npiya-is          #+#    #+#             */
/*   Updated: 2023/02/17 22:38:33 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_hand_main(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = sig_handle;
	sig.sa_flags = SA_RESTART;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

void	sig_hand_child(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = sig_child_handle;
	sig.sa_flags = SA_RESTART;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
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

void	sig_child_handle(int signo, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (signo == SIGQUIT)
		exit(121);
	if (signo == SIGINT)
		exit(130);
}
