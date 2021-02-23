/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 01:38:01 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/22 01:54:08 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *srh, size_t len)
{
	size_t j0;
	size_t j1;

	j0 = 0;
	j1 = 0;
	while (str[j0] && j0 < len)
	{
		j1 = 0;
		while (str[j0 + j1] == srh[j1] && j0 + j1 < len)
		{
			j1++;
			if (srh[j1] == '\0')
				return ((char *)str + j0);
		}
		j0++;
	}
	if (srh[j1] == '\0')
		return ((char *)str);
	return (0);
}
