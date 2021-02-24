/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 05:52:25 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/21 22:49:37 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t j;

	j = 0;
	while (src[j] && j < len)
	{
		dst[j] = src[j];
		j++;
	}
	while (j < len)
		dst[j++] = '\0';
	return (dst);
}
