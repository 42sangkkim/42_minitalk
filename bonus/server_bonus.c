/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:38:26 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/11 11:46:11 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minitalk_bonus.h"
#include "utils_bonus.h"

t_rx	g_rx;

void	put_pid(void);
void	handler(int sig, siginfo_t *siginfo, void *uap);
void	push_bit(unsigned char bit);
void	wait_signal(size_t *timer);

int	main(void)
{
	struct sigaction	sa;
	size_t				timer;

	g_rx.pid = 0;
	g_rx.sig = 0;
	if (init_sigaction(&sa, &handler) < 0)
	{
		print_error("sigaction error");
		return (-1);
	}
	push_bit(0xFF);
	put_pid();
	while (1)
	{
		g_rx.flag = 0;
		timer = TIMEOUT;
		if (g_rx.pid > 0)
			kill(g_rx.pid, g_rx.sig);
		while (!g_rx.flag)
			wait_signal(&timer);
	}
	return (0);
}

void	put_pid(void)
{
	print("server is ready!\npid is [ ");
	put_unbr((unsigned int)getpid());
	print(" ]\n");
}

void	handler(int sig, siginfo_t *siginfo, void *uap)
{
	(void)uap;
	if (g_rx.pid == 0 && siginfo->si_pid)
	{
		g_rx.pid = siginfo->si_pid;
		push_bit(0xFF);
	}
	else if (siginfo->si_pid != g_rx.pid)
	{
		print_error("signal from unknown process");
		g_rx.pid = 0;
		return ;
	}
	if (sig == SIGUSR1)
		push_bit(0);
	else
		push_bit(1);
	g_rx.sig = sig;
	g_rx.flag = 1;
}

void	push_bit(unsigned char bit)
{
	static unsigned int	buffer;

	if (bit & 0xFE)
	{
		buffer = 0x01;
		return ;
	}
	buffer = (buffer << 1) | bit;
	if (buffer & 0x100)
	{
		write(1, &buffer, 1);
		if (!(buffer & 0xFF))
		{
			print_success(" NULL character received!");
			kill(g_rx.pid, g_rx.sig);
			g_rx.pid = 0;
		}
		buffer = 0x01;
	}
}

void	wait_signal(size_t *timer)
{
	if (g_rx.pid && !(*timer--))
	{
		print_error("timeout");
		g_rx.pid = 0;
		g_rx.flag = 1;
	}
	usleep(1);
}
