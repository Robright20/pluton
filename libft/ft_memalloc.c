/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 06:05:28 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/12 14:46:56 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*r;
	size_t	j;

	j = 0;
	if (!(r = (char *)malloc(size * sizeof(*r))))
		return (NULL);
	while (j < size)
	{
		r[j] = '\0';
		j++;
	}
	return (r);
}
