/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:37:01 by mzaboub           #+#    #+#             */
/*   Updated: 2021/03/20 13:31:20 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "viz.h"

int	g_fd;

int	ft_dprintf(int fd, const char *restrict format, ...)
{
	va_list	ap;
	int		nbr;
	char	*fmt;

	nbr = 0;
	g_fd = fd;
	if (fd < 0)
		return (-1);
	va_start(ap, format);
	fmt = (char*)format;
	while (*fmt)
	{
		fmt += set_color(fmt);
		if ((*fmt == '%' && *(++fmt)) && *fmt != '%')
		{
			fmt = flag_scope(&nbr, fmt, ap);
			if (*fmt && *fmt != '%')
				nbr += write(g_fd, fmt++, 1);
		}
		else if (*fmt)
			nbr += write(g_fd, fmt++, 1);
	}
	va_end(ap);
	v_ack_await(fd);
	return (nbr);
}
