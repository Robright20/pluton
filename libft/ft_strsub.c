/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bob <bob@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 00:37:46 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/05 13:52:46 by bob              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
** you may run throug some unexpected behavior
** if [start] is out of the word boundaries.
*/

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s || !(str = (char*)malloc(len + 1)))
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = i <= start ? s[start++] : (char)0;
	str[i] = (char)0;
	return (str);
}
