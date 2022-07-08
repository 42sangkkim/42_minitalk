/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:59:28 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/08 17:01:43 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "server_bonus.h"
#include "utils.h"

t_tx

int	main(void)
{
	struct sigaction	sa;

	if (init_sigaction(&sa, &handler) == -1)
		return (-1);
	print("Server is ready\nServer pid is [ ");
	put_unbr((size_t)getpid());
	print(" ]\n");
	while (1)
	{
		if (g_tx.pid)
		{
			
			kill(g_tx.pid, g_tx.sig);
		}
		while (g_tx.flag)
		{
			if (timer--)
				usleep(1);
			else if (g_tx.sig)
			{
				print("\n\033[0;31[ERROR] Timeout\n");
				g_tx.sig = 0;
				g_tx.pid = 0;
			}
		}
	}
	return(0);
}

void	handler(int sig, siginfo_t *sip, void *uap)
{
	(void)uap;
	if (g_tx.pid == 0)
		g_tx.pid = sip->si_pid;
	else if (g_tx.pid != sip->si_pid)
	{
		print("\n\033[0;1[ERROR] Signal from wong process\n");

	
