/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 18:35:13 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/09 18:58:03 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		init_arena(t_players *players, t_game_para *parameters, int *ids_av)
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
