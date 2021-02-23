/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bob <bob@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:03:38 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/05 14:54:13 by bob              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char const *str)
{
	int		size;

	if (!str)
		return ;
	size = 0;
	while (str[size])
		size++;
	(void)(size && write(1, str, size));
}
