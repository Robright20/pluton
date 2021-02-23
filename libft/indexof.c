/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bob <bob@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 04:48:06 by bob               #+#    #+#             */
/*   Updated: 2021/01/16 16:18:30 by fokrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

ssize_t	index_of(void *str, int c, size_t size)
{
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (i < size)
	{
		if (((unsigned char*)str)[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}
