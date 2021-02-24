/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 07:29:04 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/21 22:45:58 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			j;

	j = 0;
	str = (unsigned char*)s;
	while (j < n)
	{
		if (str[j] == (unsigned char)c)
			return (&str[j]);
		j++;
	}
	return (NULL);
}
