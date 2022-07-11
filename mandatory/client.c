/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:24:09 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/11 11:48:33 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int		get_pid(pid_t *server, int c, char **v);
void	send(pid_t server, unsigned char data);

int	main(int argc, char **argv)
{
	pid_t			server;
	unsigned char	*data;

	if (get_pid(&server, argc, argv) < 0)
		return (-1);
	data = (unsigned char *)argv[2];
	while (*data)
		send(server, *data++);
	send(server, *data);
	return (0);
}

int	get_pid(pid_t *server, int argc, char **argv)
{
	if (argc != 3)
		return (-1);
	*server = 0;
	while ('0' <= *(argv[1]) && *(argv[1]) <= '9')
		*server = *server * 10 + *(argv[1])++ - '0';
	if (*argv[1])
		return (-1);
	return (0);
}

void	send(pid_t server, unsigned char data)
{
	unsigned char	mask;

	mask = 0x80;
	while (mask)
	{
		if (data & mask)
			kill(server, SIGUSR2);
		else
			kill(server, SIGUSR1);
		mask = mask >> 1;
		usleep(200);
	}
}
