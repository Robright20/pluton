/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdarg0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:13:24 by zael-mab          #+#    #+#             */
/*   Updated: 2020/03/02 23:33:48 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	a02(t_data *data, t_lol lol, const char *ar)
{
	int q;

	data->jumper = lol.x;
	data->ps = 0;
	data->pres = 0;
	while (ar[++data->jumper] && data->ps == 0)
	{
		lol.z = -1;
		q = 0;
		while (data->types[++lol.z])
		{
			if (data->types[lol.z] == ar[data->jumper])
			{
				data->ps = data->jumper;
				q = (data->jumper) - (lol.x + 1);
			}
			else if (data->ps > 0)
				break ;
		}
		if (q < 1)
			z_data_flg(data, lol, ar);
	}
}

void	z_data_flg(t_data *data, t_lol lol, const char *ar)
{
	lol.z = -1;
	while (data->f_lags[++lol.z])
		if (data->f_lags[lol.z] == ar[data->jumper])
		{
			if (lol.z == 0 && !(data->flg & MINES))
				data->flg = data->flg + (1 << lol.z);
			if ((ar[data->jumper] == '.') && ar[data->jumper + 1] == '0' &&
					(ar[data->jumper + 2] == '-'))
				data->huck = 1;
			else if (lol.z == 1 && !(data->flg & PLUS))
				data->flg = data->flg + (1 << lol.z);
			else if (lol.z == 2 && !(data->flg & HASH))
				data->flg = data->flg + (1 << lol.z);
			else if (lol.z == 3 && !(data->flg & SPACE))
				data->flg = data->flg + (1 << lol.z);
			else if (lol.z == 4 && !(data->flg & ZERO))
			{
				if (!(ft_isdigit(ar[data->jumper - 1])) &&
				(ar[data->jumper - 1] != '.') && !(data->flg & MINES))
					data->flg = data->flg + (1 << lol.z);
			}
		}
}

void	z_data_huck(t_data *data, t_lol lol, const char *ar)
{
	data->huck = 0;
	data->pres = data->ps;
	data->jumper = lol.x - 1;
	while (ar[++data->jumper] && data->jumper < data->ps)
	{
		if ((ar[data->jumper] == '.') && (ar[data->jumper + 1] == '-'))
			data->huck = 1;
		if ((ar[data->jumper] == '.') && (ar[data->ps - 1] == '-'))
			data->huck = 2;
		if ((ar[data->jumper] == '.') && (ar[data->ps - 1] == '-') &&
		(ar[data->jumper + 1] == '-'))
			data->huck = 3;
		if (ar[data->jumper] == '.')
			data->pres = data->jumper;
	}
}

void	z_data_fw(t_data *data, t_lol lol, const char *ar)
{
	data->jumper = lol.x - 1;
	data->fw1 = -1;
	data->fw0 = -1;
	while (ar[++data->jumper] && data->jumper < data->ps)
	{
		if (data->fw1 <= 0 && ft_isdigit(ar[data->jumper]) == 1 &&
		data->jumper < data->pres)
		{
			data->fw1 = ft_atoi(ar + data->jumper);
			while (ft_isdigit(ar[data->jumper]))
				data->jumper++;
		}
		else if (data->fw0 <= 0 && ft_isdigit(ar[data->jumper]) == 1 &&
		data->jumper > data->pres)
		{
			data->fw0 = ft_atoi(ar + data->jumper);
			while (ft_isdigit(ar[data->jumper]))
				data->jumper++;
		}
	}
	data->fw0 = (data->fw0 < -1 ? 6 : data->fw0);
}

void	z_data_hl(t_data *data, t_lol lol, const char *ar)
{
	data->h_flags = -1;
	data->l_flags = -1;
	data->jumper = lol.x - 1;
	while (ar[++data->jumper] && data->jumper < data->ps)
	{
		if (ar[data->jumper] == 'h')
			data->h_flags = (ar[data->jumper] == 'h' ? 1 : -1);
		if (ar[data->jumper] == 'h' && ar[data->jumper - 1] == 'h' &&
		data->h_flags == 1)
			data->h_flags = 2;
		if (ar[data->jumper] == 'l')
			data->l_flags = 1;
		if (ar[data->jumper] == 'l' && ar[data->jumper - 1] == 'l' &&
		data->l_flags == 1)
			data->l_flags = 2;
		if (ar[data->jumper] == 'L')
			data->l_flags = 3;
	}
}
