/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:43:44 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/04 17:14:45 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ldi(t_cursor *processes, t_game_para *parameters)
{
	int		index;
	int		sum;
	int		to_save;

	if (processes->args[2] > 0 && processes->args[2] < 17)
	{
		printf("P    %d | %s %d %d r%d\n", processes->player_id,
			op_tab[processes->opcode - 1].name, processes->args[0],
			processes->args[1], processes->args[2]);
		printf("          |-> store to %d + %d = %d (with pc and mod %d)\n",
			processes->args[1], processes->args[2],
			processes->args[1] + processes->args[2], processes->pc);
		sum = processes->args[0] + processes->args[1];
		index = processes->pc;
		index = (index + ((sum + MEM_SIZE) % MEM_SIZE) % IDX_MOD) % MEM_SIZE;
		to_save = get_vfarena(processes, parameters->arena, 4, index);
		processes->registeries[processes->args[2] - 1] = to_save;
	}
	return (1);
}
