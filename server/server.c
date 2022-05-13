/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:09:24 by sangkkim          #+#    #+#             */
/*   Updated: 2022/05/13 11:16:02 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h> // have to remove
#include <stdlib.h>

#include "sig_buffer.h"

void	my_sigaction(int sig, struct __siginfo *siginfo, void *handler);
void	receive_signal(pid_t from, unsigned char bit);

int	main(void)
{
	struct sigaction	sigusr_action;

	printf("server is runnig\nserver pid : %d\n", getpid());
	sigusr_action.sa_flags |= SA_SIGINFO;
	sigusr_action.sa_sigaction = my_sigaction;
	sigaction(SIGUSR1, &sigusr_action, NULL);
	sigaction(SIGUSR2, &sigusr_action, NULL);
	while (1)
		;
	return (0);
}

void	my_sigaction(int sig, struct __siginfo *siginfo, void *handler)
{
	if (sig == SIGUSR1)
		push_buffer(siginfo -> si_pid, 0);
	else if (sig == SIGUSR2)
		push_buffer(siginfo -> si_pid, 1);
	kill(siginfo -> si_pid, SIGUSR1);
}

void	push_buffer(pid_t pid, int bit)
{
	static t_buffer	*buffer_list;
	t_buffer		*buffer;

	buffer = get_buffer(buffer_list, pid);
	if (!buffer)
	{
		clear_buffer(buffer_list);
		exit(-1);
	}
	(buffer -> data) = ((buffer -> data) << 1) & bit;
	(buffer -> cnt)++;
	if ((bufßåAsfer -> cnt) % 8)
	{
		if (flush_unicode(buffer -> data))
			del_buffer(buffer_list, pid);
	}
}

int	flush_unicode(char *data, int cnt)
{
	int	code_len;
	
	code_len = 1;
	data[0]=

t_buffer	*get_buffer(t_buffer **node, pid_t pid)
{
	if (*node == NULL)
	{
		*node = malloc(sizeof(t_buffer));
		if (!(*node))
			return (NULL);
		(*node) -> next = NULL;
		(*node) -> data = 0;
		(*node) -> cnt = 0;
		(*node) -> pid = pid;
		return (*node);
	}
	else if (((*node) -> pid) == pid)
		return (*node);
	else
		return (get_buffer(((*node) -> next), pid));
}
