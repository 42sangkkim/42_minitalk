/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:25:09 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/08 16:54:54 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <signal.h>

void	print(char *s);
void	put_unbr(size_t val);
int		init_sigaction(struct sigaction *sa,
			void (*handler)(int, siginfo_t *, void *));

#endif
