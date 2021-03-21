/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strscpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:40:31 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 15:51:15 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strscpy(char *dst, const char *src, size_t s, size_t len)
{
	size_t j;

	j = -1;
	while (src[s] && s < len)
	{
		dst[++j] = src[s];
		s++;
	}
	while (j < len)
		dst[j++] = '\0';
	return (dst);
}
