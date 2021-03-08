/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:58:16 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/08 15:33:41 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int		if_arg_tind(t_cursor *processes, t_game_para *parameters, int i)
{
	int		index;
	int		value;

	index = (processes->pc + processes->args[i] % IDX_MOD) % MEM_SIZE;
	value = get_vfarena(parameters->arena, 4, index);
	return (value);
}

int		sti(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		index;
	int		sum;
	int		reg;

	index = processes->pc;
	if (size[1] == 1)
		processes->args[1] = processes->registeries[processes->args[1] - 1];
	if (size[2] == 1)
		processes->args[2] = processes->registeries[processes->args[2] - 1];
	if (processes->args[0] > 0 && processes->args[0] < 17)
	{
		printf("P %4d | %s r%d %d %d\n", processes->id,
			op_tab[processes->opcode - 1].name, processes->args[0],
			processes->args[1], processes->args[2]);
		printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			processes->args[1], processes->args[2],
			processes->args[1] + processes->args[2], processes->pc +
			processes->args[1] + processes->args[2]);
		if (size[1] == 3)
			processes->args[1] = if_arg_tind(processes, parameters, 1);
		sum = processes->args[1] + processes->args[2];
		index = (index + ((sum % IDX_MOD + MEM_SIZE) % MEM_SIZE)) % MEM_SIZE;
		reg = processes->args[0] - 1;
		cpy_toarena(processes->registeries[reg], &parameters, index, 4);
	}
	return (1);
}
