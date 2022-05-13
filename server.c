/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:09:24 by sangkkim          #+#    #+#             */
/*   Updated: 2022/05/13 18:28:49 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	putpid(int pid);
void	my_sigaction(int sig, struct __siginfo *siginfo, void *ucp);
void	push_buffer(unsigned int bit);

int	main(void)
{
	struct sigaction	sigusr_action;

	write(1, "server is running\nserver pid : ", 31);
	putpid(getpid());
	write(1, "\n", 1);
	sigusr_action.sa_flags |= SA_SIGINFO;
	sigusr_action.sa_sigaction = my_sigaction;
	sigaction(SIGUSR1, &sigusr_action, NULL);
	sigaction(SIGUSR2, &sigusr_action, NULL);
	while (1)
		;
	return (0);
}

void	putpid(int pid)
{
	char	digit;

	if (pid / 10)
		putpid(pid / 10);
	digit = pid % 10 + '0';
	write(1, &digit, 1);
}

void	my_sigaction(int sig, struct __siginfo *siginfo, void *ucp)
{
	struct sigaction	sigusr_action;

	ucp = NULL;
	sigusr_action.sa_flags |= SA_SIGINFO;
	sigusr_action.sa_sigaction = my_sigaction;	
	if (sig == SIGUSR1)
	{
		push_buffer(0);
		sigaction(SIGUSR1, &sigusr_action, NULL);
	}
	else if (sig == SIGUSR2)
	{
		push_buffer(1);
		sigaction(SIGUSR2, &sigusr_action, NULL);
	}
	kill(siginfo -> si_pid, SIGUSR1);
}

void	push_buffer(unsigned int bit)
{
	static unsigned int	buffer;

	if (buffer == 0)
		buffer = 1;
	buffer = buffer << 1 | bit;
	if (buffer & 0x100)
	{
		write(1, &buffer, 1);
		buffer = 1;
	}
}

