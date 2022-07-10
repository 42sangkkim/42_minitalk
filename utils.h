/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 01:32:11 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/11 02:03:05 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <signal.h>

// utils1.c
void	print(const char *s);
void	print_error(char *msg);
void	print_warning(char *msg);
void	print_success(char *msg);
void	put_unbr(unsigned int n);

// utils2.c
int	init_sigaction(struct sigaction *sa, \
		void (*handler)(int, siginfo_t *, void *));

#endif