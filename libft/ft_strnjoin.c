/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:41:57 by zael-mab          #+#    #+#             */
/*   Updated: 2020/02/14 21:42:00 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strnjoin(char const *s1, char const *s2, size_t n)
{
    char    *result;
    size_t    t_length;
    
    if (!s1 || !s2)
        return (NULL);
    t_length = ft_strlen((char *)s1) + n + 1;
    if (!(result = (char *)malloc(sizeof(char) * t_length)))
        return (NULL);
    return (ft_strncat(ft_strcpy(result, (char *)s1), (char *)s2, n));
}
