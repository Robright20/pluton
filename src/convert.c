/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:49:49 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/12 14:50:18 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int	convert_to_numfd(int size, int fd)
{
	unsigned char	*buffer;
	unsigned int	hex;
	int				i;

	i = -1;
	hex = 0;
	if (!(buffer = ft_memalloc(sizeof(unsigned char) * 4)))
		return (0);
	if (read(fd, buffer, size) < 0)
		return (-1);
	while (++i < size)
	{
		hex <<= 8;
		hex |= (unsigned int)buffer[i];
	}
	ft_strdel((char **)&buffer);
	return (hex);
}

int				convert_to_num(char *str, int size)
{
	int		hex;
	int		i;

	i = -1;
	hex = 0;
	while (++i < size)
	{
		hex <<= 8;
		hex |= (int)str[i];
	}
	return (hex);
}
