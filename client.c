/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:05:31 by sangkkim          #+#    #+#             */
/*   Updated: 2022/05/11 14:39:41 by sangkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	send_sig(pid_t pid, unsigned char data);

int	main(int argc, char **argv)
{
	pid_t			server_pid;
	unsigned char	buffer[1];

	if (argc < 2)
		return (-1);
	server_pid = atoi(argv[1]);
	while (1)
	{
		if (read(0, buffer, 1))
			send_sig(server_pid, *buffer);
	}
}

void	send_sig(pid_t pid, unsigned char data)
{
	int	cnt;

	cnt = 0;
	while (cnt < 8)
	{
		if (data & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(20);
		data = data >> 1;
		cnt++;
	}
}
