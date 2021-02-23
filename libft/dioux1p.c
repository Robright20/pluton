/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dioux1p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 01:03:48 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:31:34 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	it_b09(unsigned long long vl, int base, t_ayy *ayy)
{
	int x;

	ayy->n = vl;
	x = 1;
	while ((ayy->n = ayy->n / base) >= 1)
		x++;
	ayy->rar = ft_strnew(x);
	ayy->n = (vl > 0 ? vl : -vl);
	while (x--)
	{
		if (ayy->n % base < 10)
			ayy->rar[x] = ayy->n % base + '0';
		else
			ayy->rar[x] = ayy->n % base + 'a' - 10;
		ayy->n = ayy->n / base;
	}
	ayy->rar[x] = ((x == 0) ? '-' : '0');
}

int		pn_u(unsigned long long cnt)
{
	int	i;

	i = 0;
	if (cnt > 0)
		i = 1;
	return (i);
}

int		pn(long long cnt)
{
	int	i;

	i = 0;
	if (cnt >= 0)
		i = 1;
	return (i);
}

void	a04_prim(t_data data, t_cnt *cnt, va_list vl, const char *f)
{
	if (f[data.ps] == 'c')
		cnt->c = (char)va_arg(vl, int);
	else
		cnt->c = '%';
	if (!(data.flg & MINES))
	{
		cnt->total += ft_abs(data.fw1);
		if (data.flg & ZERO)
			dd(data.fw1, 1, '0');
		else
			dd(data.fw1, 1, ' ');
		ft_putchar(cnt->c);
	}
	a04_p(data, cnt);
}

void	a04_p(t_data data, t_cnt *cnt)
{
	if ((data.flg & MINES) && (data.huck == 2 || data.huck == 0))
	{
		cnt->total += ft_abs(data.fw1);
		ft_putchar(cnt->c);
		dd(data.fw1, 1, ' ');
	}
	else if (data.huck == 1 || data.huck == 3)
	{
		cnt->total += ft_abs(data.fw0);
		ft_putchar(cnt->c);
		dd(data.fw0, 1, ' ');
	}
}
