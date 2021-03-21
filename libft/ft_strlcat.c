/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 07:14:02 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/21 23:41:31 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t ld;
	size_t ls;
	size_t ln;

	ln = 0;
	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	if (ld >= size)
		ls = ls + size;
	else
		ls = ls + ld;
	while (src[ln] && ld + 1 < size)
	{
		dst[ld] = src[ln];
		ln++;
		ld++;
	}
	dst[ld] = '\0';
	return (ls);
}
