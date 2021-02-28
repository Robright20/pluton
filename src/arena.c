/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 18:35:13 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/28 12:58:12 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		init_arena(t_players *players, t_game_para *parameters)
{
	int		i;
	int		start_index;
	// int 	j;
	
	i = 0;
	if (!(parameters->arena = (char *)ft_memalloc(MEM_SIZE)))
		return (-1);
	while (++i <= players->number_of_players)
	{
		start_index = MEM_SIZE / players->number_of_players * (i - 1);
		ft_memcpy(parameters->arena + start_index, players->player[i - 1]->code,
												players->player[i - 1]->size);
	}
	// i = -1;
	// j = 0;
	// while (++i < 4096)
	// {
	// 	j++;
	// 	printf("%02hhx  ", parameters->arena[i]);
	// 	if (j == 32)
	// 	{
	// 		printf("\n");
	// 		j = 0;
	// 	}
	// 	if (i == 2047)
	// 	{
	// 		j = 0;
	// 		printf("\n\n---------------------\n\n");
	// 	}
	// }
	return (1);
}
