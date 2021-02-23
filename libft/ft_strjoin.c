/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 06:13:32 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/12 16:02:33 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	t;
	char	*s0;

	i = 0;
	t = 0;
	if (s1 && s2)
	{
		if ((s0 = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		{
			while (s1[i])
			{
				s0[i] = s1[i];
				i++;
			}
			while (s2[t])
			{
				s0[i] = s2[t];
				t++;
				i++;
			}
			return (s0);
		}
	}
	return (NULL);
}
