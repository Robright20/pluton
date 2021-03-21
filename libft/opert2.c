/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opert2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 08:58:41 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:33:23 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*get_bits(char *ptr, size_t size)
{
	int			i;
	size_t		jumper;
	char		*x;

	jumper = -1;
	x = ft_strnew(size * 8);
	ptr += size - 1;
	while (size--)
	{
		i = 8;
		while (i--)
			x[++jumper] = ((((*ptr) >> i) & 1) ? '1' : '0');
		ptr--;
	}
	return (x);
}

long long		ft_pow(long long x, long long y)
{
	long long	w;

	w = 1;
	while (y--)
		w *= x;
	return (w);
}

char			*ft_powx(char *x, int y)
{
	char		*w;
	char		*str;

	str = NULL;
	w = ft_memset(ft_strnew(y + 1), '0', y + 1);
	if (y == 0)
	{
		w[y] = '1';
		free(x);
		return (w);
	}
	if (ft_atoi(x) == 10)
	{
		w[0] = '1';
		free(x);
		return (w);
	}
	else
		return (powx0(w, y, x, str));
}

char			*powx0(char *w, int y, char *x, char *str)
{
	char		*str0;

	w[y] = '1';
	while (y > 1)
	{
		if (y % 2 == 0)
		{
			str = ft_multi(x, x);
			x = str;
			str = NULL;
			y /= 2;
		}
		else
		{
			str0 = ft_strdup(x);
			str = ft_multi(x, w);
			w = ft_strdup(str);
			x = ft_multi(str0, str0);
			free(str);
			y = (y - 1) / 2;
		}
	}
	return (ft_multi(x, w));
}

char			*ft_strev(char *x)
{
	int			i;
	int			j;
	char		*ax;

	j = 0;
	i = ft_strlen(x);
	ax = ft_strnew(i + 1);
	while (i--)
	{
		ax[j] = x[i];
		j++;
	}
	free(x);
	return (ax);
}
