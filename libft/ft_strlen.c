/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 02:01:43 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/19 00:05:39 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strlen(const char *str)
{
	int		j;

	j = 0;
	while (str[j])
		j++;
	return (j);
}

size_t		ft_strlenp(const char *str)
{
	size_t	j;

	j = 0;
	while (str[j])
		j++;
	return (j);
}
