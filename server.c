/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:09:24 by sangkkim          #+#    #+#             */
/*   Updated: 2022/05/11 14:42:19 by sangkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h> // have to remove
#include <stdlib.h>

#include "sig_buffer.h"

void	my_handler(int sig);
void	my_sigaction(int sig, struct __siginfo *siginfo, void *handler);
void	receive_signal(pid_t from, unsigned char bit);

int	main(void)
{
	struct sigaction	sigusr_action;

	printf("server is runnig\nserver pid : %d\n", getpid());
	sigusr_action.sa_flags |= SA_SIGINFO;
	sigusr_action.sa_sigaction = my_sigaction;
	sigaction(SIGUSR1, &sigusr_action, NULL);
	sigaction(SIGUSR2, &sigusr_action, NULL);
	while (1)
		;
	return (0);
}

void	my_sigaction(int sig, struct __siginfo *siginfo, void *handler)
{
	struct sigaction	sigusr_action;

	sigusr_action.sa_flags |= SA_SIGINFO;
	sigusr_action.sa_sigaction = my_sigaction;
	if (sig == SIGUSR1)
	{
		sigaction(SIGUSR1, &sigusr_action, NULL);
		receive_signal(siginfo->si_pid, 0);
	}
	else if (sig == SIGUSR2)
	{
		sigaction(SIGUSR2, &sigusr_action, NULL);
		receive_signal(siginfo->si_pid, 1);
	}
}
