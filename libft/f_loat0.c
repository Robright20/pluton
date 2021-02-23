/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_loat0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 09:10:59 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:31:44 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		f_loat(const char *ar, t_data data, t_cnt *cnt, va_list vl)
{
	t_lol	lol;

	if (data.l_flags == 3)
		cnt->c = va_arg(vl, long double);
	if (data.l_flags == -1 || data.l_flags == 1)
		cnt->c = (long double)va_arg(vl, double);
	cnt->z = get_bits((char*)&cnt->c, sizeof(cnt->c));
	cnt->a = 64;
	cnt->b = 15;
	cnt->u = 16383;
	cnt->sign = (int)cnt->z[0 + 48] - '0';
	cnt->mantissa = ft_strsub(cnt->z, cnt->b + 2 + 48, cnt->a);
	cnt->exp = ft_strsub(cnt->z, 1 + 48, cnt->b);
	f_loat0(cnt, &lol);
	if (f_loat11(data, cnt, &lol) && f_loatp(ar, data, cnt, &lol))
	{
		f_loat1(data, cnt, &lol);
		f_loat2(ar, data, cnt, &lol);
		free(lol.vf);
		free(cnt->arr);
	}
	else
		free(cnt->res);
	free(cnt->mantissa);
	free(cnt->exp);
}

void		f_loat0(t_cnt *cnt, t_lol *lol)
{
	char	*flt;
	char	*tmp;
	char	*str;
	char	*tp;

	free(cnt->z);
	lol->z = 0;
	lol->k = 0;
	cnt->res = ft_memset(ft_strnew(100), '0', 100);
	while (cnt->mantissa[lol->z])
	{
		if (cnt->mantissa[lol->z] == '1')
		{
			lol->k = lol->z + 1;
			tmp = ft_powx(ft_strdup("5"), lol->k);
			flt = ft_powx(ft_strdup("10"), (cnt->a - (lol->z + 1)));
			str = ft_multi(flt, tmp);
			tp = ft_sum(cnt->res, str);
			cnt->res = tp;
		}
		lol->z++;
	}
}

int			f_loat11(t_data data, t_cnt *cnt, t_lol *lol)
{
	if (ft_strcmp(cnt->exp, "111111111111111") == 0)
	{
		data.fw0 = (data.fw0 < 4 ? 4 : data.fw0);
		if (lol->k == 0)
		{
			if ((data.flg & SPACE) && data.fw1 < data.fw0 &&
			!(cnt->sign == 1) && !(data.flg & PLUS))
			{
				data.fw1 -= 1;
				cnt->total += ft_printf(" ");
			}
			if (cnt->sign == 1)
				cnt->arr = "-inf";
			if (data.flg & PLUS && !(cnt->sign == 1))
				cnt->arr = "+inf";
			if (!(data.flg & PLUS) && !(cnt->sign == 1))
				cnt->arr = "inf";
		}
		if (lol->k != 0)
			cnt->arr = "nan";
		a06_prim(data, cnt);
		return (0);
	}
	return (1);
}

void		flgas(t_data data, t_cnt *cnt)
{
	data.fw0 = (data.fw0 == -1 ? 0 : data.fw0);
	if ((data.flg & SPACE) && cnt->sign != 1 && !(data.flg & PLUS)
	&& (data.flg & MINES))
	{
		cnt->total += ft_printf(" ");
		cnt->x += 1;
	}
	if (cnt->sign == 1 && (data.flg & MINES))
		cnt->total += ft_printf("-");
	if ((data.flg & PLUS) && (cnt->sign != 1) && (data.flg & MINES))
		cnt->total += ft_printf("+");
}

int			f_loatp(const char *ar, t_data data, t_cnt *cnt, t_lol *lol)
{
	if (ft_strcmp(cnt->exp, "000000000000000") == 0 && lol->k == 0)
	{
		cnt->x = 0;
		if (ar[data.pres] != '.' && data.fw0 == -1)
			data.fw0 = 6;
		f_3bita(data, cnt);
		if (!(data.flg & MINES))
			f_4bita(data, cnt);
		flgas(data, cnt);
		cnt->total += ft_printf("0");
		if (data.fw0 > 0 || (data.flg & HASH))
			cnt->total += ft_printf(".");
		if (ar[data.ps] != '.' && data.fw0 > 0)
		{
			cnt->total += data.fw0;
			dd(data.fw0, 0, '0');
		}
		if ((data.flg & MINES))
			f_4bita(data, cnt);
		return (0);
	}
	return (1);
}
