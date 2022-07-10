/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:22:11 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/08 13:35:29 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int		flag;
int		tx_sig;
pid_t	server_pid;
size_t	sent;

pid_t	get_pid(int argc, char **argv);
void	init_client_sa(struct sigaction *sa);
void	client_handler(int sig, siginfo_t *siginfo, void *uap);
void	send_data(unsigned char byte);
void	ft_putnbr(size_t val);

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	unsigned char		*data;

	server_pid = get_pid(argc, argv);
	init_client_sa(&sa);
	data = (unsigned char *)argv[2];
	sent = 0;
	while (*data)
	{
		send_data(*data);
		data++;
	}
	send_data(*data);
	return (0);
}

pid_t	get_pid(int argc, char **argv)
{
	char	*pid_s;
	pid_t	pid;

	if (argc != 3)
		exit(-1);
	pid = 0;
	pid_s = argv[1];
	while (*pid_s)
	{
		if ('0' <= *pid_s && *pid_s <= '9')
			pid = pid * 10 + *pid_s - '0';
		else
			exit(-1);
		pid_s++;
	}
	return (pid);
}

void	init_client_sa(struct sigaction *sa)
{
	sa->sa_sigaction = client_handler;
	sigemptyset(&(sa->sa_mask));
	sigaddset(&(sa->sa_mask), SIGUSR1);
	sigaddset(&(sa->sa_mask), SIGUSR2);
	sa->sa_flags = 0 | SA_SIGINFO;
	if (sigaction(SIGUSR1, sa, NULL) == -1)
		exit(-1);
	if (sigaction(SIGUSR2, sa, NULL) == -1)
		exit(-1);
}

void	client_handler(int sig, siginfo_t *siginfo, void *uap)
{
	(void)uap;
	if (server_pid != siginfo->si_pid || sig != tx_sig)
	{
		write(1, "\n[ERROR]\n", 9);
		flag = 0;
		return ;
	}
	flag = 1;
	tx_sig = 0;
}

void	send_data(unsigned char byte)
{
	unsigned char	mask;
	size_t			time_out;

	mask = 0b10000000;
	while (mask)
	{
		flag = 0;
		if (!(byte & mask))
			tx_sig = SIGUSR1;
		else
			tx_sig = SIGUSR2;
		time_out = 10000;
		kill(server_pid, tx_sig);
		while (!flag)
		{
			if (!(time_out--))
			{
				write(1, "Server is dead\n err in ", 23);
				ft_putnbr(sent);
				write(1, " bit\n", 5);
				exit(-1);
			}
			usleep(1);
		}
		sent++;
		mask = mask >> 1;
	}
}

void	ft_putnbr(size_t val)
{
	char	digit;

	if (val / 10)
		ft_putnbr(val / 10);
	digit = val % 10 + '0';
	write(1, &digit, 1);
}
