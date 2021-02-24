/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 22:58:40 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/22 01:52:40 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *srh)
{
	int	j0;
	int	j1;

	j0 = 0;
	j1 = 0;
	while (str[j0])
	{
		j1 = 0;
		while (str[j0 + j1] == srh[j1])
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
