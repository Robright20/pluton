/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 18:35:13 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/12 14:42:33 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			init_arena(t_players *players, t_game_para *parameters, int *ids_av)
{
	int		i;
	int		j;
	int		start_index;

	i = 0;
	j = 0;
	if (!(parameters->arena = (char *)ft_memalloc(MEM_SIZE)))
		return (-1);
	while (++i <= 4)
		if (ids_av[i - 1] == 1)
		{
			start_index = MEM_SIZE / players->number_of_players * j;
			ft_memcpy(parameters->arena + start_index,
				players->player[i - 1]->code, players->player[i - 1]->size);
			j++;
		}
	return (1);
}

void		cpy_toarena(int reg, t_game_para **parameters, int index, int n)
{
	int		i;
	int		tmp;

	i = index % MEM_SIZE;
	index = index + n;
	tmp = (n - 1) * 8;
	while (i < index)
	{
		(*parameters)->arena[i] = (reg >> tmp) & 255;
		i = (i + 1) % MEM_SIZE;
		(i == 0) && (index %= MEM_SIZE);
		tmp -= 8;
	}
}

int			dump_arena(t_game_para *parameters)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	printf("0x0000 : ");
	while (++i < 4096)
	{
		j++;
		printf("%02hhx ", parameters->arena[i]);
		if (j % 64 == 0)
		{
			printf("\n");
			(j != 4096) && printf("0x%04x : ", j);
		}
	}
	return (1);
}
