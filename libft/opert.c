/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opert.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 14:22:37 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 15:45:53 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_multi(char *ar, char *ax)
{
	t_ayy	ayy;

	ayy.y0 = ft_strlen(ax);
	ayy.y1 = ft_strlen(ar);
	ayy.rar = ft_memset(ft_strnew(ayy.y0 + ayy.y1), '0', (ayy.y0 + ayy.y1));
	ayy.sum = 0;
	ayy.w0 = -1;
	if (ayy.y1 == 0 || ayy.y0 == 0)
	{
		if (ft_strcmp(ax, ar))
			free(ar);
		free(ax);
		return (ayy.rar);
	}
	ft_multi0(ar, ax, &ayy);
	if (ft_strcmp(ax, ar))
		free(ar);
	free(ax);
	return (ignor(ft_strev(ayy.rar)));
}

void		ft_multi0(char *ar, char *ax, t_ayy *ayy)
{
	while (--ayy->y1 >= 0)
	{
		ayy->looper = ++ayy->w0;
		ayy->carry = 0;
		ayy->y0 = ft_strlen(ax);
		while (--ayy->y0 >= 0)
		{
			ayy->sum = (ar[ayy->y1] - '0') * (ax[ayy->y0] - '0') +
			(ayy->rar[ayy->looper] - '0') + ayy->carry;
			ayy->rar[ayy->looper++] = ((ayy->sum % 10) + '0');
			ayy->carry = ayy->sum / 10;
		}
		ayy->rar[ayy->looper] += (ayy->carry > 0 ? ayy->carry : 0);
	}
}

char		*ft_sum(char *ar, char *ax)
{
	t_ayy	ayy;

	if (ft_strlen(ax) > ft_strlen(ar))
	{
		ayy.tmp = ax;
		ax = ar;
		ar = ayy.tmp;
	}
	ar = ft_strev(ar);
	ax = ft_strev(ax);
	ft_sump(ax, ar, &ayy);
	while (++ayy.looper < ayy.w0)
	{
		ayy.y0 = (ar[ayy.looper] - '0') +
			(ayy.looper < ayy.w1 ? (ax[ayy.looper] - '0') : 0) + ayy.carry;
		ayy.rar[ayy.looper] = (ayy.y0 % 10) + '0';
		ayy.carry = ayy.y0 / 10;
	}
	free(ar);
	free(ax);
	if (ayy.carry)
		ayy.rar[ayy.looper++] = '1';
	return (ignor(ft_strev(ayy.rar)));
}

void		ft_sump(char *ax, char *ar, t_ayy *ayy)
{
	ayy->w0 = ft_strlen(ar);
	ayy->w1 = ft_strlen(ax);
	ayy->rar = ft_strnew(ayy->w0 + ayy->w1);
	ayy->looper = -1;
	ayy->carry = 0;
}

int			ft_abs(int x)
{
	return (x < 0 ? -x : x);
}
