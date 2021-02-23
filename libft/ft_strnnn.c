/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnnn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 10:10:52 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:32:40 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		f_loat1(t_data data, t_cnt *cnt, t_lol *lol)
{
	char	*tst;
	char	*ten;

	tst = l_exponnt(cnt->exp, cnt->u, lol);
	ten = ft_powx(ft_strdup("10"), cnt->a);
	lol->vf = ft_multi(ft_sum(ten, cnt->res), tst);
	cnt->arr = ft_strsub(lol->vf, 0, ft_strlen(lol->vf));
	lol->d = ft_strlen(lol->vf) - cnt->a - ft_abs(lol->y);
	lol->d = ft_abs(lol->d);
	lol->r = ft_strlen(lol->vf) - cnt->a;
	data.fw0 = (data.fw0 == -1 ? 0 : data.fw0);
}

void		f_loat2(const char *ar, t_data data, t_cnt *cnt, t_lol *lol)
{
	if (ar[data.pres] != '.' && data.fw0 == -1)
		data.fw0 = 6;
	if (lol->y < 0)
		f_loat3(lol->vf, data, cnt, lol);
	if (lol->y == 0)
		f_loat5(data, cnt, lol);
	if (lol->y > 0)
	{
		f_loat6(lol->vf, data, cnt, lol);
		if (data.fw1 > data.fw0 && (data.flg & MINES))
			f_4bita(data, cnt);
	}
}

void		f_loat6(const char *vf, t_data data, t_cnt *cnt, t_lol *lol)
{
	data.fw0 = (data.fw0 == -1 ? 0 : data.fw0);
	f_loat00((lol->r + data.fw0), lol, cnt, lol->vf);
	f_3bita(data, cnt);
	cnt->x += lol->r - 1 + (ft_strlen(vf) < ft_strlen(cnt->arr));
	if (!(data.flg & MINES))
		f_4bita(data, cnt);
	flgas(data, cnt);
	lol->tmp = ft_strsub(cnt->arr, 0, lol->r +
	(ft_strlen(vf) < ft_strlen(cnt->arr)));
	cnt->total += ft_printf("%s", lol->tmp);
	free(lol->tmp);
	if (data.fw0 > 0 || data.flg & HASH)
		cnt->total += ft_printf(".");
	if (data.fw0 > 0)
	{
		lol->tmp = ft_strsub(cnt->arr, lol->r, data.fw0);
		cnt->total += ft_printf("%s", lol->tmp);
		free(lol->tmp);
		if (data.fw0 > ft_strlen(cnt->arr) - lol->r)
		{
			cnt->total += (data.fw0 - ft_strlen(cnt->arr) + lol->r);
			dd((data.fw0 - ft_strlen(cnt->arr) + lol->r), 0, '0');
		}
	}
}

void		f_loat5(t_data data, t_cnt *cnt, t_lol *lol)
{
	data.fw0 = (data.fw0 >= 0 ? data.fw0 : 0);
	f_loat00(data.fw0 + 1, lol, cnt, lol->vf);
	f_3bita(data, cnt);
	if (!(data.flg & MINES))
		f_4bita(data, cnt);
	flgas(data, cnt);
	lol->tmp = ft_strsub(cnt->arr, 0, 1);
	cnt->total += ft_printf("%s", lol->tmp);
	free(lol->tmp);
	if (data.fw0 > 0 || (data.flg & HASH))
		cnt->total += ft_printf(".");
	if (data.fw0 > 0)
	{
		lol->tmp = ft_strsub(cnt->arr, 1, data.fw0);
		cnt->total += ft_printf("%s", lol->tmp);
		free(lol->tmp);
	}
	if (data.fw0 > ft_strlen(cnt->arr) - lol->r)
	{
		cnt->total += (data.fw0 - ft_strlen(cnt->arr) + lol->r);
		dd((data.fw0 - ft_strlen(cnt->arr) + lol->r), 0, '0');
	}
	if ((data.flg & MINES))
		f_4bita(data, cnt);
}

void		dd(int i, int j, char b)
{
	while (i-- > j)
		ft_putchar(b);
}
