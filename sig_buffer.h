/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_buffer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:46:29 by sangkkim          #+#    #+#             */
/*   Updated: 2022/05/11 14:42:41 by sangkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_BUFFER_H
# define SIG_BUFFER_H

typedef struct s_sig_buffer
{
	pid_t				pid;
	unsigned char		data;
	int					cnt;
	struct s_sig_buffer	*next;
}	t_sig_buffer;

#endif