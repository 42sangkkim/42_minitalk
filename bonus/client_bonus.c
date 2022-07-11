/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:22:11 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/11 11:46:22 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "minitalk_bonus.h"
#include "utils_bonus.h"

t_tx	g_tx;

pid_t	get_pid(int argc, char **argv);
void	handler(int sig, siginfo_t *siginfo, void *uap);
void	send_data(unsigned char byte);

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	unsigned char		*data;

	g_tx.pid = get_pid(argc, argv);
	if (g_tx.pid == 0)
		return (-1);
	if (init_sigaction(&sa, handler) < 0)
	{
		print_error("sigaction error");
		return (-1);
	}
	data = (unsigned char *)argv[2];
	while (*data)
	{
		send_data(*data);
		data++;
	}
	send_data(*data);
	return (0);
}

pid_t	get_pid(int argc, char **argv)
{
	char	*pid_s;
	pid_t	pid;

	if (argc != 3)
	{
		print_warning("wrong format 'client [server pid] [message to send]'");
		return (0);
	}
	pid = 0;
	pid_s = argv[1];
	while (*pid_s)
	{
		if ('0' <= *pid_s && *pid_s <= '9')
			pid = pid * 10 + *pid_s - '0';
		else
		{
			print_warning("wrong character in server pid");
			return (0);
		}
		pid_s++;
	}
	return (pid);
}

void	handler(int sig, siginfo_t *siginfo, void *uap)
{
	(void)uap;
	if (g_tx.pid != siginfo->si_pid || sig != g_tx.sig)
	{
		print_error("a signal from unknown process");
		g_tx.echo_received = 0;
		return ;
	}
	g_tx.echo_received = 1;
	g_tx.sig = 0;
}

void	send_data(unsigned char byte)
{
	unsigned char	mask;
	size_t			timer;

	mask = 0b10000000;
	while (mask)
	{
		g_tx.echo_received = 0;
		if (!(byte & mask))
			g_tx.sig = SIGUSR1;
		else
			g_tx.sig = SIGUSR2;
		timer = TIMEOUT;
		kill(g_tx.pid, g_tx.sig);
		while (!g_tx.echo_received)
		{
			if (!(timer--))
			{
				print_error("timeout");
				exit(-1);
			}
			usleep(1);
		}
		mask = mask >> 1;
	}
}
