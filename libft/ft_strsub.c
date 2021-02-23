/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 05:53:27 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/12 16:01:56 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s1, unsigned int start, size_t len)
{
	char	*s0;
	size_t	j;

	j = 0;
	if (!s1 || !(s0 = (char *)malloc(len + 1 * sizeof(*s0))))
		return (NULL);
	while (j < len)
	{
		s0[j] = s1[j + start];
		j++;
	}
	s0[j] = '\0';
	return (s0);
}
