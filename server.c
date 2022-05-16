/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:09:24 by sangkkim          #+#    #+#             */
/*   Updated: 2022/05/16 12:33:10 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	put_pid(int pid);
void	my_sigaction(int sig, struct __siginfo *siginfo, void *uap);
void	push_buffer(unsigned int bit);

int	main(void)
{
	struct sigaction	sigusr_action;

	write(1, "server is running\nserver pid : ", 31);
	put_pid(getpid());
	write(1, "\n", 1);
	sigusr_action.sa_flags &= ~SA_RESETHAND;
	sigusr_action.sa_flags |= SA_SIGINFO;
	sigusr_action.sa_sigaction = my_sigaction;
	if (sigaction(SIGUSR1, &sigusr_action, NULL) == -1)
		exit(-1);
	if (sigaction(SIGUSR2, &sigusr_action, NULL) == -1)
		exit(-1);
	while (1)
		;
	return (0);
}

void	put_pid(int pid)
{
	char	digit;

	if (pid / 10)
		put_pid(pid / 10);
	digit = pid % 10 + '0';
	write(1, &digit, 1);
}

void	my_sigaction(int sig, struct __siginfo *siginfo, void *uap)
{
	(void)uap;
	if (sig == SIGUSR1)
		push_buffer(0);
	else if (sig == SIGUSR2)
		push_buffer(1);
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
		if (buffer & 0xFF)
		{
			write(1, &buffer, 1);
		}
		else
			write(1, "\nreceive complete!\n", 19);
		buffer = 1;
	}
}
