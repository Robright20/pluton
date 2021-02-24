/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 06:30:28 by zael-mab          #+#    #+#             */
/*   Updated: 2020/02/05 13:01:39 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long	ft_x(unsigned long long nb)
{
	size_t					j;

	j = 1;
	while (nb / 10)
	{
		nb = nb / 10;
		j++;
	}
	return (j);
}

char						*ft_itoa_u(unsigned long long n)
{
	char					*str;
	int						y;
	unsigned long long		nb;

	nb = n;
	y = ft_x(n);
	if (!(str = ft_strnew(y)))
		return (NULL);
	while (y > 0)
	{
		str[y - 1] = nb % 10 + 48;
		nb = nb / 10;
		y--;
	}
	return (str);
}
