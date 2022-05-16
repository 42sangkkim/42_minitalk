/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:09:24 by sangkkim          #+#    #+#             */
/*   Updated: 2022/05/16 14:59:47 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int		main(void);
void	put_pid(int pid);
void	ft_server_sigaction(int sig, struct __siginfo *siginfo, void *uap);
void	push_buffer(unsigned int bit);
int		write_utf8(unsigned char *buffer, unsigned int cnt);

int	main(void)
{
	struct sigaction	sigusr_action;

	write(1, "server is running\nserver pid : ", 31);
	put_pid(getpid());
	write(1, "\n", 1);
	sigusr_action.sa_flags &= ~SA_RESETHAND;
	sigusr_action.sa_flags |= SA_SIGINFO;
	sigusr_action.sa_sigaction = ft_server_sigaction;
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

void	get_signal(int sig, struct __siginfo *siginfo, void *uap)
{
	(void)uap;
	if (sig == SIGUSR1)
		push_buffer(0);
	else if (sig == SIGUSR2)
		push_buffer(1);
	usleep(10);
	kill(siginfo -> si_pid, SIGUSR1);
}

void	push_buffer(unsigned int bit)
{
	static unsigned int	buffer;
	static unsigned int	cnt;

	buffer |= bit << cnt++;
	if (cnt == 8)
	{
		if (write_utf8((unsigned char *)&buffer, cnt) > 0)
		{
			if ((unsigned char)buffer == 0)
				write(1, "\nreceive complete!\n", 19);
			cnt = 0;
			buffer = 0x00000000;
		}
	}
	else if (cnt > 32)
	{
		write(2, "buffer overflow\n", 16);
		exit(-1);
	}
}

int	write_utf8(unsigned char *buffer, unsigned int cnt)
{
	if (cnt == 8 && (*buffer & 0b10000000) == 0b00000000)
		return (write(1, buffer, 1));
	else if (cnt == 16 && (*buffer & 0b11100000) == 0b11000000)
		return (write(1, buffer, 2));
	else if (cnt == 24 && (*buffer & 0b11110000) == 0b11100000)
		return (write(1, buffer, 3));
	else if (cnt == 32 && (*buffer & 0b11111000) == 0b11110000)
		return (write(1, buffer, 4));
	else
		return (0);
}
