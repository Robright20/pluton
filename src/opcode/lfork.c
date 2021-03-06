/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:51:44 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/06 23:28:38 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			lfork(t_cursor *processes, t_game_para *parameters,
														t_cursor **fprocesses)
{
	int			index;
	t_cursor	*new_process;

	printf("P %4d | %s %d (%d)\n", processes->id,
		op_tab[processes->opcode - 1].name, processes->args[0],
										processes->pc + processes->args[0]);
	index = (processes->args[0] + MEM_SIZE) % MEM_SIZE;
	if (!(new_process = fork_child(processes, fprocesses)))
		return (-1);
	new_process->pc = (index + processes->pc) % MEM_SIZE;
	new_process->opcode = parameters->arena[new_process->pc];
	if (new_process->opcode < 1 || new_process->opcode > 16)
		new_process->pc = (new_process->pc + 1) % MEM_SIZE;
	else
		new_process->wait_cycle =
			op_tab[new_process->opcode - 1].cycle_to_wait;
	*fprocesses = new_process;
	return (1);
}
