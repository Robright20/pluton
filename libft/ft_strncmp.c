/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:50:04 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/12 14:39:58 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while ((((unsigned char)s1[i] || (unsigned char)s2[i])) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strscmp(const char *s1, const char *s2, size_t s, size_t n)
{
	size_t i;

	i = 0;
	while ((((unsigned char)s1[i] || (unsigned char)s2[s])) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[s])
			return ((unsigned char)s1[i] - (unsigned char)s2[s]);
		i++;
		s++;
	}
	return (0);
}
