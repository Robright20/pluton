/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bo.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:18:14 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:45:49 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_printf(const char *f, ...)
{
	t_cnt		cnt;
	t_lol		lol;
	va_list		vl;

	lol.x = 0;
	cnt.total = 0;
	va_start(vl, f);
	while (f[lol.x] != '\0')
	{
		if (f[lol.x] != '%')
		{
			cnt.total += ft_printf("%c", f[lol.x]);
			lol.x++;
		}
		else if (f[lol.x] == '%')
		{
			if (!trt(&cnt, &lol, f, vl))
				return (cnt.total);
		}
		else
			lol.x++;
	}
	va_end(vl);
	return (cnt.total);
}

int				trt(t_cnt *cnt, t_lol *lol, const char *f, va_list vl)
{
	t_data		data;

	data.f_lags = ft_strdup("-+# 0");
	data.types = ft_strdup("cpdeiosuxX%f");
	data.flg = 0;
	a02(&data, *lol, f);
	z_data_huck(&data, *lol, f);
	z_data_fw(&data, *lol, f);
	z_data_hl(&data, *lol, f);
	if (data.ps == 0)
		lol->x++;
	else
	{
		print_typs(data, f, cnt, vl);
		lol->x = data.ps + 1;
		free(data.f_lags);
		free(data.types);
	}
	return (1);
}

void			print_typs(t_data data, const char *f, t_cnt *cnt, va_list vl)
{
	if (f[data.ps] == 'c' || f[data.ps] == '%')
		a04_prim(data, cnt, vl, f);
	if (f[data.ps] == 's')
	{
		cnt->arr = va_arg(vl, char *);
		a06_prim(data, cnt);
	}
	if (f[data.ps] == 'p')
		a10prim(data, cnt, f, vl);
	if (f[data.ps] == 'd' || f[data.ps] == 'i')
	{
		f_lags1(data, cnt, vl);
		a11d_prim(data, f, cnt);
	}
	if (f[data.ps] == 'o' || f[data.ps] == 'u' ||
			f[data.ps] == 'x' || f[data.ps] == 'X')
		f_lags0(data, cnt, vl);
	if (f[data.ps] == 'o')
		a10prim0(data, cnt, f);
	if (f[data.ps] == 'u')
		a11d_prim(data, f, cnt);
	if (f[data.ps] == 'x' || f[data.ps] == 'X')
		a10prim(data, cnt, f, vl);
	if (f[data.ps] == 'f')
		f_loat(f, data, cnt, vl);
}

void			f_lags0(t_data data, t_cnt *cnt, va_list vl)
{
	if (data.h_flags == 1)
		cnt->c = (unsigned short int)va_arg(vl, unsigned int);
	if (data.h_flags == 2)
		cnt->c = (unsigned char)va_arg(vl, int);
	if (data.l_flags == 1)
		cnt->c = va_arg(vl, unsigned long int);
	if (data.l_flags == 2)
		cnt->c = va_arg(vl, unsigned long long int);
	if (data.l_flags == -1 && data.h_flags == -1)
		cnt->c = va_arg(vl, unsigned int);
}

void			f_lags1(t_data data, t_cnt *cnt, va_list vl)
{
	if (data.h_flags == 1)
		cnt->c = (short int)va_arg(vl, int);
	if (data.h_flags == 2)
		cnt->c = (signed char)va_arg(vl, int);
	if (data.l_flags == 1)
		cnt->c = va_arg(vl, long int);
	if (data.l_flags == 2)
		cnt->c = va_arg(vl, long long int);
	if (data.l_flags == -1 && data.h_flags == -1)
		cnt->c = va_arg(vl, int);
}
