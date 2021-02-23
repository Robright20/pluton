/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <fokrober@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 07:31:39 by fokrober          #+#    #+#             */
/*   Updated: 2020/12/26 07:31:56 by fokrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_xputstr(char const *str)
{
	size_t	size;

	if (!str)
		return (0);
	size = 0;
	while (str[size])
		size++;
	(void)(size && write(1, str, size));
	return (size);
}
