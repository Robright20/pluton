/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 05:30:25 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/12 16:00:02 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	j;
	char	*str;

	j = 0;
	if (s)
	{
		if ((str = ft_strnew(ft_strlen(s))))
		{
			while (s[j])
			{
				str[j] = f(j, s[j]);
				j++;
			}
			return (str);
		}
	}
	return (NULL);
}
