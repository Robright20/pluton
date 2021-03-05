/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:58:16 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/05 18:46:26 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int		sti(t_cursor *processes, t_game_para *parameters)
{
	int		index;
	int		sum;
	int		reg;

	index = processes->pc;
	printf("P    %d | %s r%d %d %d\n", processes->id,
		op_tab[processes->opcode - 1].name, processes->args[0],
		processes->args[1], processes->args[2]);
	printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
		processes->args[1], processes->args[2],
		processes->args[1] + processes->args[2], processes->pc +
		processes->args[1] + processes->args[2]);
	if (processes->args[0] > 0 && processes->args[0] < 17)
	{
		sum = processes->args[1] + processes->args[2];
		index = (index + ((sum % IDX_MOD + MEM_SIZE) % MEM_SIZE)) % MEM_SIZE;
		reg = processes->args[0] - 1;
		cpy_toarena(processes->registeries[reg], parameters, index, 4);
	}
	return (1);
}
