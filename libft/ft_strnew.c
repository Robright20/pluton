/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 07:28:17 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/12 14:49:20 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*r;
	size_t	j;

	j = 0;
	if (!(r = (char *)malloc(size + 1 * sizeof(*r))))
		return (NULL);
	while (j <= size)
		r[j++] = '\0';
	return (r);
}
