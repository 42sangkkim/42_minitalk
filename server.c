/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:38:26 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/08 13:35:25 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

pid_t	rx_pid;
int		rx_sig;
int		rx_flag;
size_t	rx_cnt;

void	init_server_sa(struct sigaction *sa);
void	server_handler(int sig, siginfo_t *siginfo, void *uap);
void	push_bit(unsigned char bit);
void	put_nbr(size_t val);

int	main(void)
{
	struct sigaction	sa;
	size_t				timeout;

	rx_pid = 0;
	rx_sig = 0;
	rx_flag = 0;
	init_server_sa(&sa);
	push_bit(0xFF);
	write(1, "server is ready!\npid is [ ", 26);
	put_nbr((size_t)getpid());
	write(1, " ]\n", 3);
	while (1)
	{
		if (rx_pid > 0)
		{
			rx_flag = 0;
			rx_cnt++;
			timeout = 10000;
			kill(rx_pid, rx_sig);
		}
		while (!rx_flag)
		{
			if (rx_pid && !timeout--)
			{
				write(1, "\n[ERROR]\ntimeout : I received ", 30);
				put_nbr(rx_cnt);
				write(1, "bits\n", 5);
				rx_pid = 0;
			}
			usleep(1);
		}
	}
	return (0);
}

void	init_server_sa(struct sigaction *sa)
{
	sa->sa_sigaction = server_handler;
	sigemptyset(&(sa->sa_mask));
	sigaddset(&(sa->sa_mask), SIGUSR1);
	sigaddset(&(sa->sa_mask), SIGUSR2);
	sa->sa_flags = 0 | SA_SIGINFO;
	if (sigaction(SIGUSR1, sa, NULL) == -1)
		exit(-1);
	if (sigaction(SIGUSR2, sa, NULL) == -1)
		exit(-1);
}

void	server_handler(int sig, siginfo_t *siginfo, void *uap)
{
	(void)uap;
	if (rx_pid == 0 && siginfo->si_pid)
	{
		rx_cnt = 0;
		rx_pid = siginfo->si_pid;
		push_bit(0xFF);
	}
	else if (siginfo->si_pid != rx_pid)
	{
		write(1, "\n[ERROR]\nclient pid : \n", 23);
		put_nbr((size_t)rx_pid);
		write(1, "\nreceived   : ", 14);
		put_nbr((size_t)siginfo->si_pid);
		write(1, "\n", 1);
		rx_pid = 0;
		return ;
	}
	if (sig == SIGUSR1)
		push_bit(0);
	else
		push_bit(1);
	rx_sig = sig;
	rx_flag = 1;
}

void	push_bit(unsigned char bit)
{
	static unsigned int	buffer;

	if (bit & 0xFE)
	{
		buffer = 0x01;
		return ;
	}
	buffer  = (buffer << 1) | bit;
	if (buffer & 0x100)
	{
		write(1, &buffer, 1);
		if (!(buffer & 0xFF))
		{
			write(1, "\nNULL charactor received!\n", 26);
			kill(rx_pid, rx_sig);
			rx_pid = 0;
			write(1, "I received ", 11);
			put_nbr(rx_cnt);
			write(1, " bits\n", 6);
		}
		buffer = 0x01;
	}
}

void	put_nbr(size_t val)
{
	char	digit;

	if (val / 10)
		put_nbr(val / 10);
	digit = val % 10 + '0';
	write(1, &digit, 1);
}
