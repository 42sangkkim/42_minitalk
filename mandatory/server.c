/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:11:34 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/11 11:47:31 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	put_pid(pid_t n);
void	handler(int sig);

int	main(void)
{
	if (signal(SIGUSR1, handler) < 0)
		return (-1);
	if (signal(SIGUSR2, handler) < 0)
		return (-1);
	put_pid(getpid());
	write(1, "\n", 1);
	while (1)
		;
	return (0);
}

void	put_pid(pid_t n)
{
	char	digit;

	if (n / 10)
		put_pid(n / 10);
	digit = n % 10 + '0';
	write(1, &digit, 1);
}

void	handler(int sig)
{
	static unsigned char	buffer;
	static size_t			cnt;

	if (sig == SIGUSR1)
		buffer = buffer << 1 | 0x00;
	else if (sig == SIGUSR2)
		buffer = buffer << 1 | 0x01;
	cnt++;
	if (cnt == 0x08)
	{
		write(1, &buffer, 1);
		cnt = 0;
		if (!buffer)
			write(1, "\n[SUCCESS]\n", 11);
	}
}
