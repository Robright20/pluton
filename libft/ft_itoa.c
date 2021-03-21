/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 09:16:45 by zael-mab          #+#    #+#             */
/*   Updated: 2020/02/03 02:58:14 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long		ft_x(long long nb)
{
	size_t	j;

	j = 1;
	while (nb / 10)
	{
		nb = nb / 10;
		j++;
	}
	return (j);
}

long long				ft_llabs(long long n)
{
	return (n > 0 ? n : -n);
}

char					*ft_itoa(long long n)
{
	char				*str;
	int					y;
	int					z;
	unsigned long long	nb;

	nb = n;
	y = ft_x(n);
	z = (n < 0 ? 1 : 0);
	if (!(str = ft_strnew(y + z)))
		return (NULL);
	if (z)
		n = ft_llabs(n);
	while (y > 0)
	{
		str[y - 1] = nb % 10 + 48;
		nb = nb / 10;
		y--;
	}
	return (str);
}
