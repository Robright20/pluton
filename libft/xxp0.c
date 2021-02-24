/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxp0.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 03:10:30 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:34:11 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	xxp2_p(t_ayy ayy, t_data data, t_cnt *cnt)
{
	if (cnt->x == 2)
		ft_putstr(cnt->arr);
	if (data.huck == 1 || data.huck == 3)
	{
		ayy.w0 = data.fw0 - ayy.y0 - cnt->x;
		ft_putstr(ayy.rar);
		dd(ayy.w0, 0, ' ');
	}
	else if (data.huck == 2 || data.huck == 0)
	{
		ayy.w0 = data.fw0 - ayy.y0;
		dd(ayy.w0, 0, 48);
		ft_putstr(ayy.rar);
	}
	cnt->total += ayy.w0;
}

void	xxp_3(t_ayy ayy, t_data data, t_cnt *cnt)
{
	if (!(data.flg & MINES))
	{
		dd(ayy.w1, 0, ' ');
		if (cnt->x == 2)
			ft_putstr(cnt->arr);
		dd(ayy.w0, 0, 48);
		ft_putstr(ayy.rar);
	}
	else if ((data.flg & MINES) && (data.huck == 2 || data.huck == 0))
	{
		if (cnt->x == 2)
			ft_putstr(cnt->arr);
		dd(ayy.w0, 0, '0');
		ft_putstr(ayy.rar);
		dd(ayy.w1, 0, ' ');
	}
	else if (data.huck == 1 || data.huck == 3)
	{
		if (cnt->x == 2)
			ft_putstr(cnt->arr);
		ft_putstr(ayy.rar);
		dd(ayy.w0, 0, ' ');
	}
}
