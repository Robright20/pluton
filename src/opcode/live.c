/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:55:51 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/06 12:56:07 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		live(t_cursor *processes, t_game_para *parameters)
{
	printf("P %4d | %s %d\n", processes->id,
		op_tab[processes->opcode - 1].name, processes->args[0]);
	if (processes->args[0] < 0 && processes->args[0] > -5)
	{
		printf("Player %d (%s) is said to be alive\n", -processes->args[0],
			parameters->players->player[-processes->args[0] - 1]->name);
		parameters->last_live = -processes->args[0];
		parameters->live_counter++;
		processes->last_live = parameters->cycle_counter;
	}
	return (1);
}
