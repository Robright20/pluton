/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:20:27 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/10 17:21:19 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		lld(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		index;

	if (processes->args[1] > 0 && processes->args[1] < 17)
	{
		if (size[0] == 3)
		{
			index = (processes->pc + processes->args[0]) % MEM_SIZE;
			processes->args[0] = get_vfarena(parameters->arena, 4, index);
		}
		if ((parameters->verbos >> 2) & 1)
			printf("P %4d | %s %d r%d\n", processes->id,
			op_tab[processes->opcode - 1].name, processes->args[0],
			processes->args[1]);
		processes->registeries[processes->args[1] - 1] = processes->args[0];
		(processes->args[0] == 0) && (processes->carry = 1);
		(processes->args[0] != 0) && (processes->carry = 0);
	}
	return (1);
}
