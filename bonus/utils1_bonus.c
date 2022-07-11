/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 01:06:54 by sangkkim          #+#    #+#             */
/*   Updated: 2022/07/11 11:46:32 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print(const char *s)
{
	while (*s)
		write(1, s++, 1);
}

void	print_error(char *msg)
{
	const char	*prefix = "\n\033[0;31m[ERROR] ";
	const char	*suffix = "\n\033[0;30m";

	print(prefix);
	print(msg);
	print(suffix);
}

void	print_warning(char *msg)
{
	const char	*prefix = "\n\033[0;33m[WARNING] ";
	const char	*suffix = "\n\033[0;30m";

	print(prefix);
	print(msg);
	print(suffix);
}

void	print_success(char *msg)
{
	const char	*prefix = "\n\033[0;32m[SUCCESS] ";
	const char	*suffix = "\n\033[0;30m";

	print(prefix);
	print(msg);
	print(suffix);
}

void	put_unbr(unsigned int n)
{
	char	digit;

	if (n / 10)
		put_unbr(n / 10);
	digit = n % 10 + '0';
	write(1, &digit, 1);
}
