/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popac.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:06:25 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:33:34 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		a06_prim(t_data data, t_cnt *cnt)
{
	t_ayy	ayy;

	if (!cnt->arr)
		cnt->arr = "(null)";
	ayy.y0 = ft_strlen(cnt->arr);
	if (data.ps != data.pres)
	{
		if (data.fw0 >= ayy.y0)
			ayy.w1 = data.fw1 - ayy.y0;
		else if (data.fw0 < 0)
			ayy.w1 = data.fw1;
		else if (data.fw0 < ayy.y0)
			ayy.w1 = data.fw1 - data.fw0;
		if (data.huck == 1 || data.huck == 3)
		{
			cnt->total += (data.fw0 > 0 ? data.fw0 : 0);
			dd(data.fw0, 0, ' ');
		}
		z_06_str1(data, cnt, &ayy);
	}
	z_06_str2(data, cnt, &ayy);
}

void		z_06_str1(t_data data, t_cnt *cnt, t_ayy *ayy)
{
	if (data.huck == 0 && !(data.flg & MINES))
	{
		if (data.fw0 > 0)
			cnt->total += (data.fw0 > ayy->y0 ? ayy->y0 : data.fw0);
		cnt->total += (ayy->w1 > 0 ? ayy->w1 : 0);
		dd(ayy->w1, 0, ' ');
		while (data.fw0-- > 0 && *cnt->arr != '\0')
			ft_putchar(*cnt->arr++);
	}
	z_06_sp(data, cnt, ayy);
}

void		z_06_sp(t_data data, t_cnt *cnt, t_ayy *ayy)
{
	if ((data.huck == 2 || data.huck == 0) && (data.flg & MINES))
	{
		if (data.fw0 > 0)
			cnt->total += (data.fw0 > ayy->y0 ? ayy->y0 : data.fw0);
		cnt->total += (ayy->w1 > 0 ? ayy->w1 : 0);
		while (data.fw0-- > 0 && *cnt->arr != '\0')
			ft_putchar(*cnt->arr++);
		dd(ayy->w1, 0, ' ');
	}
}

void		z_06_str2(t_data data, t_cnt *cnt, t_ayy *ayy)
{
	if (data.pres == data.ps)
	{
		ayy->w1 = (data.fw1 > ayy->y0) ? (data.fw1 - ayy->y0) : 0;
		cnt->total += ayy->w1 + ayy->y0;
		if (!(data.flg & MINES))
		{
			dd(ayy->w1, 0, ' ');
			ft_putstr(cnt->arr);
		}
		else if (data.flg & MINES)
		{
			ft_putstr(cnt->arr);
			dd(ayy->w1, 0, ' ');
		}
	}
}

void		diu_3(t_data data, t_cnt *cnt, t_ayy *ayy)
{
	if ((data.flg & MINES) && (data.huck == 2 || data.huck == 0))
	{
		cnt->total += (ayy->w0 > 0 ? ayy->w0 : 0) + (ayy->w1 > 0 ? ayy->w1 : 0);
		if (ayy->looper == 1)
			cnt->total += ft_printf("%c", ayy->a);
		dd(ayy->w0, 0, '0');
		cnt->total += ft_printf("%s", ayy->rar);
		dd(ayy->w1, 0, ' ');
	}
	else if (data.huck == 1 || data.huck == 3)
	{
		if (ayy->looper == 1)
			cnt->total += ft_printf("%c", ayy->a);
		ayy->w0 = data.fw0 - ayy->y1;
		cnt->total += ft_printf("%s", ayy->rar) + (ayy->w0 > 0 ? ayy->w0 : 0);
		dd(ayy->w0, 0, ' ');
	}
}
