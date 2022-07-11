/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 01:25:04 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/11 11:05:37 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# define TIMEOUT 10000

typedef struct s_tx
{
	int	pid;
	int	sig;
	int	echo_received;
}	t_tx;

typedef struct s_rx
{
	int	pid;
	int	sig;
	int	flag;
}	t_rx;

#endif