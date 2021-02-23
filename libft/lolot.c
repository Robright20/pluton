/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lolot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 01:35:56 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:32:52 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ignor(char *r)
{
	t_ayy		ayy;

	ayy.w0 = 0;
	ayy.looper = 0;
	while (r[ayy.looper])
	{
		if (r[ayy.looper] == '0')
			ayy.looper++;
		else
		{
			ayy.rar = ft_strnew(ft_strlen(r) - ayy.looper);
			while (r[ayy.looper])
			{
				ayy.rar[ayy.w0] = r[ayy.looper];
				ayy.w0++;
				ayy.looper++;
			}
			if (ayy.w0 != 0)
			{
				free(r);
				return (ayy.rar);
			}
		}
	}
	return (r);
}

char			*expennt(char *str, int a)
{
	int			len;
	int			j;
	char		*res;

	len = ft_strlen(str);
	j = len;
	res = ft_memset(ft_strnew(a), '0', a);
	while (j >= 0)
	{
		if (str[j] == '1')
			res = ft_sum(res, ft_powx(ft_strdup("2"), (len - j - 1)));
		j--;
	}
	return (ignor(res));
}

char			*l_exponnt(char *ar, int x, t_lol *lol)
{
	int			len;
	int			j;
	char		*tab;
	long long	res;

	len = ft_strlen(ar);
	j = len;
	res = 0;
	while (j >= 0)
	{
		if (ar[j] == '1')
			res += ft_pow(2, (len - j - 1));
		j--;
	}
	res = (res == 0 ? (1 - x) : (res - x));
	lol->y = res;
	if (res < 0)
		tab = ft_powx(ft_strdup("5"), ft_abs(res));
	else
		tab = ft_powx(ft_strdup("2"), res);
	return (ignor(tab));
}

int				ft_iszero(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

void			f_loat00(int a, t_lol *lol, t_cnt *cnt, char *vf)
{
	char		*x;
	char		*tp;
	int			y;

	lol->p = 0;
	y = (int)vf[a];
	if (y < '5')
		y = -1;
	else if (y == '5' && ft_iszero(vf + a + 1))
		y = 0;
	else
		y = 1;
	if (a <= ft_strlen(vf) && (y == 1 ||
	(y == 0 && ((int)vf[a - 1] % 2 == 1))))
	{
		lol->p = 1;
		a = ft_strlen(vf) - a;
		x = ft_powx(ft_strdup("10"), a);
		tp = ft_strdup(lol->vf);
		free(cnt->arr);
		cnt->arr = ft_sum(tp, x);
	}
}
