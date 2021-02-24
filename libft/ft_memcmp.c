/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 00:14:47 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/22 01:47:16 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str0;
	unsigned char	*str1;
	size_t			j;

	str0 = (unsigned char *)s1;
	str1 = (unsigned char *)s2;
	j = 0;
	while (j < n)
	{
		if (str0[j] != str1[j])
			return (str0[j] - str1[j]);
		j++;
	}
	return (0);
}
