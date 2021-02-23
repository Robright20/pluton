/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_loat1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 03:08:32 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:31:57 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	f_3bita(t_data data, t_cnt *cnt)
{
	cnt->x = 1;
	cnt->lg = ' ';
	data.fw0 = (data.fw0 == -1 ? 0 : data.fw0);
	if (cnt->sign == 1)
		cnt->x += 1;
	if ((data.flg & PLUS) && (cnt->sign != 1))
		cnt->x += 1;
	if (data.fw0 > 0 || data.flg & HASH)
		cnt->x += 1;
	if ((data.flg & ZERO) && !(data.flg & MINES))
		cnt->lg = '0';
}

void	f_4bita(t_data data, t_cnt *cnt)
{
	if ((data.fw0 + cnt->x) < data.fw1 && cnt->lg != '0')
	{
		cnt->x = data.fw1 - (cnt->x + data.fw0);
		cnt->total += (cnt->x > 0 ? cnt->x : 0);
		dd(cnt->x, 0, cnt->lg);
	}
	if (cnt->sign == 1 && !(data.flg & MINES))
		cnt->total += ft_printf("-");
	if ((data.flg & PLUS) && (cnt->sign != 1) && !(data.flg & MINES))
		cnt->total += ft_printf("+");
	if (data.flg & SPACE && cnt->sign != 1 && !(data.flg & PLUS)
	&& (data.fw0 + cnt->x >= data.fw1 || cnt->lg == '0') && !(data.flg & MINES))
	{
		cnt->total += ft_printf(" ");
		cnt->x += 1;
	}
	if ((data.fw0 + cnt->x) < data.fw1 && cnt->lg == '0' && !(data.flg & MINES))
	{
		cnt->x = data.fw1 - (cnt->x + data.fw0);
		cnt->total += (cnt->x > 0 ? cnt->x : 0);
		dd(cnt->x, 0, cnt->lg);
	}
}

void	f_loat3(const char *vf, t_data data, t_cnt *cnt, t_lol *lol)
{
	if (lol->d <= data.fw0)
		lol->tp = data.fw0 - lol->d;
	else
		lol->tp = lol->d;
	f_loat00(lol->tp, lol, cnt, cnt->arr);
	f_3bita(data, cnt);
	if (!(data.flg & MINES))
		f_4bita(data, cnt);
	flgas(data, cnt);
	if (ft_strlen(vf) < ft_strlen(cnt->arr))
	{
		lol->d -= 1;
		if (ft_strlen(vf) == 65)
			lol->d = 0;
		if (ft_strlen(vf) == 65)
			cnt->total += ft_printf("1");
		else
			cnt->total += ft_printf("0");
	}
	else
		cnt->total += ft_printf("0");
	f_loat3p(vf, data, cnt, lol);
}

void	f_loat3p(const char *vf, t_data data, t_cnt *cnt, t_lol *lol)
{
	if (data.fw0 > 0 || data.flg & HASH)
		cnt->total += ft_printf(".");
	if (data.fw0 < lol->d)
		lol->d = data.fw0;
	if (lol->d > 0)
	{
		cnt->total += lol->d;
		dd(lol->d, 0, '0');
	}
	if (ft_strlen(vf) < ft_strlen(cnt->arr))
		lol->tmp = ft_strsub(cnt->arr,
		(ft_strlen(vf) == 65), data.fw0 - lol->d);
	else
		lol->tmp = ft_strsub(cnt->arr, 0, (data.fw0 - lol->d));
	cnt->total += ft_printf("%s", lol->tmp);
	free(lol->tmp);
	if (data.fw0 > 0)
	{
		if (data.fw0 > lol->d + ft_strlen(cnt->arr))
			cnt->total += (data.fw0 - lol->d) - ft_strlen(cnt->arr);
		dd(((data.fw0 - lol->d) - ft_strlen(cnt->arr)), 0, '0');
	}
	if (data.flg & MINES)
		f_4bita(data, cnt);
}
