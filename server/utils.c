/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:35:06 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/08 15:47:45 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	print(char *s)
{
	while (*s)
		write(1, s++, 1);
}

void	put_unbr(size_t val)
{
	char	digit;

	if (val / 10)
		put_unbr(val / 10);
	digit = val % 10 + '0';
	write(1, &digit, 1);
}

pid_t	get_pid(char *s)
{
	pid_t	val;

	val = 0;
	while (*s)
	{
		if ('0' <= val && val <= '9')
			val = val * 10 + *s - '0';
		s++;
	}
	return (val);
}

int	init_sigaction(struct sigaction *sa,
		void (*handler)(int, siginfo_t *, void *))
{
	sigset_t	sa_mask;

	sa->sa_sigaction = handler;
	sigemptyset(&sa_mask);
	sigaddset(&sa_mask, SIGUSR1);
	sigaddset(&sa_mask, SIGUSR2);
	sa->sa_mask = sa_mask;
	sa->sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, sa, NULL) == -1)
	{
		print("[ERROR] sigaction error\n");
		return (-1);
	}
	if (sigaction(SIGUSR2, sa, NULL) == -1)
	{
		print("[ERROR] sigaction error\n");
		return (-1);
	}
	return (0);
}
