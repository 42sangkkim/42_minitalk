/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:05:31 by sangkkim          #+#    #+#             */
/*   Updated: 2022/05/13 18:08:11 by sangkkim         ###   ########.fr       */
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
		return (-1);
	signal(SIGUSR1, get_ack);
	server_pid = get_pid(argv[1]);
	data = (unsigned char *)argv[2];
	while (*data)
	{
		send_a_byte(server_pid, *data);
		data++;
	}
	send_a_byte(server_pid, *data);
	write(1, "complete!\n", 10);
}

pid_t	get_pid(char *str)
{
	pid_t	pid;

	pid = 0;
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			exit(-1);
		pid = pid * 10 + (*str - '0');
		str++;
	}
	return (pid);
}

void	get_ack(int sig)
{
	if (sig != SIGUSR1)
		pause();
}

void	send_a_byte(pid_t pid, unsigned char byte)
{
	unsigned char	bit_mask;

	bit_mask = 0b10000000;
	while (bit_mask)
	{
		if ((bit_mask & byte) == 0)
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		bit_mask = bit_mask >> 1;
		pause();
	}
}
