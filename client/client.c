/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:05:31 by sangkkim          #+#    #+#             */
/*   Updated: 2022/05/16 15:03:52 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

pid_t	get_pid(char *str);
void	get_ack(int sig);
void	send_a_byte(pid_t pid, unsigned char byte);

int	main(int argc, char **argv)
{
	pid_t			server_pid;
	unsigned char	*data;

	if (argc != 3)
	{
		write(1, "use client like this './client [pid] [message]'\n", 48);
		exit (-1);
	}
	if (signal(SIGUSR1, ft_client_sigaction))
		exit (-1);
	server_pid = get_pid(argv[1]);
	data = (unsigned char *)argv[2];
	while (*data)
	{
		send_a_byte(server_pid, *data);
		data++;
	}
	send_a_byte(server_pid, *data);
	write(1, "send complete!\n", 15);
}

pid_t	get_pid(char *str)
{
	pid_t	pid;

	pid = 0;
	while (*str)
	{
		if (*str < '0' || '9' < *str)
		{
			write(1, "pid must be digits\n", 19);
			exit(-1);
		}
		pid = pid * 10 + (*str - '0');
		str++;
	}
	return (pid);
}

void	ft_client_sigaction(int sig)
{
	if (sig != SIGUSR1)
	{
		write(2, "wrong ack\n", 10);
		pause();
	}
}

void	send_a_byte(pid_t pid, unsigned char byte)
{
	unsigned char	bit_mask;

	bit_mask = 0b00000001;
	while (bit_mask)
	{
		if ((bit_mask & byte) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
		bit_mask = bit_mask << 1;
		usleep(10);
	}
}
