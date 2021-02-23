/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dioux0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 06:36:09 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:31:09 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		a10prim0(t_data data, t_cnt *cnt, const char *ar)
{
	t_ayy	ayy;

	it_b09(cnt->c, 8, &ayy);
	if (!cnt->c && data.fw0 <= 0 && ar[data.pres] == '.')
		ayy.rar[0] = '\0';
	ayy.y0 = ft_strlen(ayy.rar);
	cnt->x = (data.flg & HASH ? 1 : 0);
	if (data.fw1 > (ayy.y0 + cnt->x) && data.fw0 <= ayy.y0)
	{
		if (cnt->c || cnt->x != 1)
			ayy.w1 = data.fw1 - ayy.y0 - cnt->x;
		else
			ayy.w1 = data.fw1 - cnt->x;
		o_01(ayy, data, cnt, ar);
	}
	o_02(ayy, data, cnt);
	if (data.fw0 > ayy.y0 && data.fw1 > data.fw0)
		o_03(ayy, data, cnt);
	free(ayy.rar);
}

void		o_01(t_ayy ayy, t_data data, t_cnt *cnt, const char *ar)
{
	if (!(data.flg & MINES))
	{
		if (data.flg & ZERO && ar[data.pres] != '.')
			dd(ayy.w1, 0, '0');
		else
			dd(ayy.w1, 0, ' ');
		if (cnt->x == 1)
			cnt->total += ft_printf("%c", '0');
		if (cnt->c || cnt->x != 1)
			cnt->total += ft_printf("%s", ayy.rar);
		cnt->total += (ayy.w1 > 0 ? ayy.w1 : 0);
	}
	else if (data.flg & MINES)
	{
		if (cnt->x == 1)
			cnt->total += ft_printf("%c", '0');
		if (cnt->c || cnt->x != 1)
			cnt->total += ft_printf("%s", ayy.rar);
		dd(ayy.w1, 0, ' ');
		cnt->total += (ayy.w1 > 0 ? ayy.w1 : 0);
	}
}

void		o_02(t_ayy ayy, t_data data, t_cnt *cnt)
{
	if (data.fw1 <= data.fw0 && data.fw0 > ayy.y0)
	{
		ayy.w0 = data.fw0 - ayy.y0;
		if (data.huck == 1 || data.huck == 3)
		{
			cnt->total += ft_printf("%s", ayy.rar) + (ayy.w0 > 0 ? ayy.w0 : 0);
			dd(ayy.w0, 0, ' ');
		}
		else if (data.huck == 2 || data.huck == 0)
		{
			dd(ayy.w0, 0, '0');
			cnt->total += ft_printf("%s", ayy.rar) + (ayy.w0 > 0 ? ayy.w0 : 0);
		}
	}
	else if ((data.fw0 <= ayy.y0 && data.fw1 <= ayy.y0 + cnt->x))
	{
		if (cnt->x == 1)
			cnt->total += ft_printf("%c", '0');
		if (cnt->c || cnt->x != 1)
			cnt->total += ft_printf("%s", ayy.rar);
	}
}

void		o_03(t_ayy ayy, t_data data, t_cnt *cnt)
{
	ayy.w0 = data.fw0 - ayy.y0;
	ayy.w1 = data.fw1 - data.fw0;
	if (!(data.flg & MINES))
	{
		dd(ayy.w1, 0, ' ');
		dd(ayy.w0, 0, 48);
		cnt->total += ft_printf("%s", ayy.rar);
		cnt->total += (ayy.w0 > 0 ? ayy.w0 : 0) + (ayy.w1 > 0 ? ayy.w1 : 0);
	}
	else if ((data.flg & MINES) && (data.huck == 2 || data.huck == 0))
	{
		dd(ayy.w0, 0, 48);
		cnt->total += ft_printf("%s", ayy.rar);
		cnt->total += (ayy.w0 > 0 ? ayy.w0 : 0) + (ayy.w1 > 0 ? ayy.w1 : 0);
		dd(ayy.w1, 0, ' ');
	}
	else if (data.huck == 1 || data.huck == 3)
	{
		ayy.w0 = data.fw0 - ayy.y1;
		cnt->total += ft_printf("%s", ayy.rar) + (ayy.w0 > 0 ? ayy.w0 : 0);
		dd(ayy.w0, 0, ' ');
	}
}
