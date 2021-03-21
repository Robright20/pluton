/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 03:10:20 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:33:59 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		a10prim(t_data data, t_cnt *cnt, const char *ar, va_list vl)
{
	t_ayy	ayy;

	if (ar[data.ps] == 'p')
	{
		cnt->c = va_arg(vl, unsigned long);
		it_b09(cnt->c, 16, &ayy);
		cnt->x = 2;
		if (!cnt->c && data.fw0 <= 0 && ar[data.pres] == '.')
			ayy.rar[0] = '\0';
	}
	it_b09(cnt->c, 16, &ayy);
	cnt->arr = "0x";
	if (ar[data.ps] != 'p')
		xxp_0(ayy, data, cnt, ar);
	xxp_1(ayy, data, cnt, ar);
	free(ayy.rar);
}

void		xxp_0(t_ayy ayy, t_data data, t_cnt *cnt, const char *ar)
{
	cnt->i = -1;
	cnt->x = 0;
	if (!cnt->c && data.fw1 < 0 && data.fw0 <= 0 && ar[data.pres] == '.')
		ayy.rar[0] = '\0';
	if (cnt->c == 0 && data.fw0 <= 0 && ar[data.pres] == '.' && data.fw1 <= 0)
		ayy.rar[0] = '\0';
	if (cnt->c == 0 && data.fw0 <= 0 && ar[data.pres] == '.' && data.fw1 > 0)
		ayy.rar[0] = ' ';
	if (ar[data.ps] == 'X')
	{
		cnt->arr = "0X";
		while (ayy.rar[++cnt->i])
		{
			if (ayy.rar[cnt->i] >= 'a' && ayy.rar[cnt->i] <= 'f')
				ayy.rar[cnt->i] = ayy.rar[cnt->i] - 32;
		}
	}
	if (cnt->c != 0)
		cnt->x = (data.flg & HASH ? 2 : 0);
}

void		xxp_1(t_ayy ayy, t_data data, t_cnt *cnt, const char *ar)
{
	ayy.y0 = ft_strlen(ayy.rar);
	cnt->total += ayy.y0 + cnt->x;
	if (data.fw1 > (ayy.y0 + cnt->x) && data.fw0 <= ayy.y0)
	{
		ayy.w1 = data.fw1 - ayy.y0 - cnt->x;
		cnt->total += ayy.w1;
		xxp_1p(ayy, data, cnt, ar);
	}
	xxp_2(ayy, data, cnt);
}

void		xxp_1p(t_ayy ayy, t_data data, t_cnt *cnt, const char *ar)
{
	if (!(data.flg & MINES))
	{
		if (data.flg & ZERO && ar[data.pres] != '.')
		{
			if (cnt->x == 2)
				ft_putstr(cnt->arr);
			dd(ayy.w1, 0, '0');
		}
		else
		{
			dd(ayy.w1, 0, ' ');
			if (cnt->x == 2)
				ft_putstr(cnt->arr);
		}
		ft_putstr(ayy.rar);
	}
	else
	{
		if (cnt->x == 2)
			ft_putstr(cnt->arr);
		ft_putstr(ayy.rar);
		dd(ayy.w1, 0, ' ');
	}
}

void		xxp_2(t_ayy ayy, t_data data, t_cnt *cnt)
{
	if (data.fw1 <= (data.fw0 + cnt->x) && data.fw0 > ayy.y0)
		xxp2_p(ayy, data, cnt);
	else if (data.fw0 <= ayy.y0 && data.fw1 <= ayy.y0 + cnt->x)
	{
		if (cnt->x == 2)
			ft_putstr(cnt->arr);
		ft_putstr(ayy.rar);
	}
	else if (data.fw0 > ayy.y0 && data.fw1 > (data.fw0 + cnt->x))
	{
		ayy.w0 = data.fw0 - ayy.y0;
		ayy.w1 = data.fw1 - data.fw0 - cnt->x;
		cnt->total += ayy.w1 + ayy.w0;
		xxp_3(ayy, data, cnt);
	}
}
