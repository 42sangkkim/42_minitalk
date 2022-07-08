/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:31:32 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/08 16:58:01 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "client_bonus.h"
#include "utils.h"

t_tx_info	g_tx;

int		get_pid(char *s);
void	handler(int sig, siginfo_t *sip, void *uap);
int		send_data(unsigned char *data);
int		send_byte(unsigned char byte);

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
	{
		print("\033[0;33m[INFO] 'client [server pid] [data to send]'\n");
		exit(-1);
	}
	g_tx.pid = get_pid(argv[1]);
	if (g_tx.pid < 0)
	{
		print("\033[0;33m[INFO] wring character in pid\n");
		exit(-1);
	}
	if (init_sigaction(&sa, &handler) == -1)
		exit(-1);
	if (send_data((unsigned char *)argv[2]) == -1)
		exit(-1);
	print("\033[0;32m[SUCCESS]\n");
	return (0);
}

int	get_pid(char *s)
{
	int	pid;

	pid = 0;
	while (*s)
	{
		if (*s < '0' || '9' < *s)
			return (-1);
		else
			pid = pid * 10 + *s - '0';
		s++;
	}
	return (pid);
}

void	handler(int sig, siginfo_t *sip, void *uap)
{
	(void)uap;
	if (sip->si_pid != (pid_t)g_tx.pid)
		print("\033[0;31m[ERROR] signal from unknown process\n");
	else if (sig != g_tx.sig)
		print("\033[0;31m[ERROR] wrong signal from server\n");
	else
		g_tx.sig = 0;
}

int	send_data(unsigned char *data)
{
	while (*data)
	{
		if (send_byte(*data++) == -1)
			return (-1);
	}
	if (send_byte(*data) == -1)
		return (-1);
	return (0);
}

int	send_byte(unsigned char byte)
{
	unsigned char	mask;
	size_t			timer;

	mask = 0x80;
	while (mask)
	{
		if (byte & mask)
			g_tx.sig = SIGUSR2;
		else
			g_tx.sig = SIGUSR1;
		timer = TIMEOUT;
		kill(g_tx.pid, g_tx.sig);
		while (g_tx.sig)
		{
			if (timer--)
				usleep(1);
			else
			{
				print("\033[0;31m[ERROR] timeout\n");
				return (-1);
			}
		}
		mask = mask >> 1;
	}
	return (0);
}
