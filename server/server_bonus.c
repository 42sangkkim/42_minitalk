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

int	main(void)
{
	struct sigaction	sa;

	if (init_sigaction(&sa, &handler) == -1)
		return (-1);
	
