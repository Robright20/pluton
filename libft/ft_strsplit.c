/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:04:26 by zael-mab          #+#    #+#             */
/*   Updated: 2019/04/22 02:27:48 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_cc(char const *s, char c, int i)
{
	int j;

	j = 0;
	while (s[i] && s[i] != c)
	{
		j++;
		i++;
	}
	return (j);
}

static	int	ft_wc(char const *s, char c)
{
	int j;
	int i;
	int f;

	i = 0;
	j = 0;
	f = 0;
	while (s[i])
	{
		if (s[i] != c && f == 0)
		{
			j++;
			f = 1;
		}
		else if (s[i] == c)
			f = 0;
		i++;
	}
	return (j);
}

char		**ft_strsplit(char const *s, char c)
{
	int		j;
	int		i;
	int		k;
	char	**str;

	i = 0;
	j = 0;
	if (!s || !(str = (char **)malloc(sizeof(char*) * (ft_wc(s, c) + 1))))
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			k = 0;
			if (!(str[j] = ft_strnew(ft_cc(s, c, i))))
				return (NULL);
			while (s[i] != c && s[i])
				str[j][k++] = s[i++];
			str[j++][k] = '\0';
		}
	}
	str[j] = NULL;
	return (str);
}
