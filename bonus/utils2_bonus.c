/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 01:51:34 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/11 11:46:34 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>

int	init_sigaction(struct sigaction *sa, \
		void (*handler)(int, siginfo_t *, void *))
{
	sa->sa_sigaction = handler;
	sigemptyset(&(sa->sa_mask));
	sigaddset(&(sa->sa_mask), SIGUSR1);
	sigaddset(&(sa->sa_mask), SIGUSR2);
	sa->sa_flags = 0 | SA_SIGINFO;
	if (sigaction(SIGUSR1, sa, (void *)0) == -1)
		return (-1);
	if (sigaction(SIGUSR2, sa, (void *)0) == -1)
		return (-1);
	return (0);
}
