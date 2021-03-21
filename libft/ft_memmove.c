/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 07:08:47 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/22 01:38:52 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *ls;

	if ((ls = (char *)malloc(sizeof(char) * (len))))
	{
		ls = ft_memcpy(ls, src, len);
		dst = ft_memcpy(dst, ls, len);
		free(ls);
	}
	return (dst);
}
