/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 06:40:24 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/22 01:12:00 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*r;
	size_t			j;
	unsigned char	*d;
	unsigned char	*s;

	r = 0;
	j = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (j < n && r == 0)
	{
		d[j] = s[j];
		if (s[j] == (unsigned char)c)
			r = d + j + 1;
		j++;
	}
	return (r);
}
