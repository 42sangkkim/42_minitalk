/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:20:44 by sangkkim          #+#    #+#             */
/*   Updated: 2022/05/11 14:42:10 by sangkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include "sig_buffer.h"

t_sig_buffer	*new_socket(pid_t pid);
t_sig_buffer	*find_socket(t_sig_buffer *head, pid_t from);
int				delete_socket(t_sig_buffer *head, pid_t pid);

void	receive_signal(pid_t from, unsigned char bit)
{
	static t_sig_buffer	head;
	t_sig_buffer		*socket;

	socket = find_socket(&head, from);
	bit = bit << (socket->cnt)++;
	socket->data |= bit;
	if (socket->cnt == 8)
	{
		write(1, &(socket->data), 1);
		delete_socket(&head, from);
	}
}

t_sig_buffer	*new_socket(pid_t pid)
{
	t_sig_buffer	*new_socket;

	new_socket = malloc(sizeof(t_sig_buffer));
	if (!new_socket)
		return (NULL);
	bzero(new_socket, sizeof(t_sig_buffer));
	new_socket->pid = pid;
	return (new_socket);
}

t_sig_buffer	*find_socket(t_sig_buffer *head, pid_t pid)
{
	while (head->next != NULL)
	{
		if (head->next->pid == pid)
			return (head->next);
		head = head->next;
	}
	head->next = new_socket(pid);
	return (head->next);
}

int	delete_socket(t_sig_buffer *head, pid_t pid)
{
	t_sig_buffer	*tmp;

	while (head->next != NULL)
	{
		if (head->next->pid == pid)
		{
			tmp = head->next->next;
			free(head->next);
			head->next = tmp;
			return (0);
		}
		head = head->next;
	}
	return (-1);
}
