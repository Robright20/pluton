/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dioux1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 06:36:09 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:31:23 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		a11d_prim(t_data data, const char *ar, t_cnt *cnt)
{
	t_ayy	ayy;

	ayy.n = cnt->c;
	ayy.looper = 0;
	if (!cnt->c)
		cnt->c = 0;
	if (ar[data.ps] == 'u')
	{
		cnt->c = (!(pn_u(cnt->c)) ? -ayy.n : ayy.n);
		ayy.rar = ft_itoa_u(cnt->c);
	}
	else
	{
		ayy.a = (((data.flg & PLUS) && pn(cnt->c)) ? '+' : '-');
		if ((data.flg & SPACE) && pn(cnt->c) && !(data.flg & PLUS))
			ayy.a = ' ';
		if (!(pn(cnt->c)) || ((data.flg & PLUS || data.flg & SPACE)))
			ayy.looper = 1;
		cnt->c = (!(pn(cnt->c)) ? -ayy.n : ayy.n);
		ayy.rar = ft_itoa(cnt->c);
	}
	diu_0(data, ar, cnt, &ayy);
	free(ayy.rar);
}

void		diu_0(t_data data, const char *ar, t_cnt *cnt, t_ayy *ayy)
{
	ayy->y2 = ft_strlen(ayy->rar);
	ayy->y1 = ayy->y2 + ayy->looper;
	ayy->w1 = 0;
	ayy->w0 = 0;
	if ((ar[data.pres] == '.') && (data.fw0 <= 0 && cnt->c == 0))
	{
		ayy->y1 -= 1;
		*ayy->rar = '\0';
	}
	if (data.fw1 > ayy->y1 && data.fw0 <= ayy->y2)
	{
		ayy->w1 = data.fw1 - ayy->y1;
		if (!(MINES & data.flg) && !(data.flg & ZERO))
		{
			dd(ayy->w1, 0, ' ');
			if (ayy->looper == 1)
				cnt->total += ft_printf("%c", ayy->a);
			cnt->total += ft_printf("%s", ayy->rar) +
			(ayy->w1 > 0 ? ayy->w1 : 0);
		}
		diu_11(data, ar, cnt, ayy);
	}
	diu_1(data, cnt, ayy);
	diu_2(data, cnt, ayy);
}

void		diu_11(t_data data, const char *ar, t_cnt *cnt, t_ayy *ayy)
{
	if (data.flg & ZERO && !(data.flg & MINES))
	{
		if (ar[data.pres] != '.')
		{
			if (ayy->looper == 1)
				cnt->total += ft_printf("%c", ayy->a);
			dd(ayy->w1, 0, '0');
		}
		else
		{
			dd(ayy->w1, 0, ' ');
			if (ayy->looper == 1)
				cnt->total += ft_printf("%c", ayy->a);
		}
		cnt->total += ft_printf("%s", ayy->rar) + (ayy->w1 > 0 ? ayy->w1 : 0);
	}
	else if (data.flg & MINES)
	{
		if (ayy->looper == 1)
			cnt->total += ft_printf("%c", ayy->a);
		cnt->total += ft_printf("%s", ayy->rar) + (ayy->w1 > 0 ? ayy->w1 : 0);
		dd(ayy->w1, 0, ' ');
	}
}

void		diu_1(t_data data, t_cnt *cnt, t_ayy *ayy)
{
	if (data.fw1 <= (data.fw0 + ayy->looper) && data.fw0 > ayy->y2)
	{
		if (ayy->looper == 1)
			cnt->total += ft_printf("%c", ayy->a);
		if (data.huck == 1 || data.huck == 3)
		{
			ayy->w0 = data.fw0 - ayy->y1;
			cnt->total += ft_printf("%s", ayy->rar) +
			(ayy->w1 > 0 ? ayy->w1 : 0);
			dd(ayy->w1, 0, ' ');
		}
		else if (data.huck == 2 || data.huck == 0)
		{
			ayy->w0 = data.fw0 - ayy->y2;
			dd(ayy->w0, 0, '0');
			cnt->total += ft_printf("%s", ayy->rar) +
			(ayy->w0 > 0 ? ayy->w0 : 0);
		}
	}
	else if (data.fw0 <= ayy->y1 && data.fw1 <= ayy->y1)
	{
		if (ayy->looper == 1)
			cnt->total += ft_printf("%c", ayy->a);
		cnt->total += ft_printf("%s", ayy->rar);
	}
}

void		diu_2(t_data data, t_cnt *cnt, t_ayy *ayy)
{
	if (data.fw0 > ayy->y2 && data.fw1 > (data.fw0 + ayy->looper))
	{
		ayy->w1 = data.fw1 - (data.fw0 + ayy->looper);
		ayy->w0 = data.fw0 - ayy->y2;
		if (!(MINES & data.flg))
		{
			dd(ayy->w1, 0, ' ');
			cnt->total += (ayy->w1 > 0 ? ayy->w1 : 0);
			if (ayy->looper == 1)
				cnt->total += ft_printf("%c", ayy->a);
			dd(ayy->w0, 0, '0');
			cnt->total += ft_printf("%s", ayy->rar) +
			(ayy->w0 > 0 ? ayy->w0 : 0);
		}
		diu_3(data, cnt, ayy);
	}
}
