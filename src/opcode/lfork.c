/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:51:44 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/04 19:26:12 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			lfork(t_cursor *processes, t_game_para *parameters,
														t_cursor **fprocesses)
{
	int			index;
	t_cursor	*new_process;

	printf("P    %d | %s %d\n", processes->player_id,
		op_tab[processes->opcode - 1].name, processes->args[0]);
	index = (processes->args[0] + MEM_SIZE) % MEM_SIZE;
	if (!(new_process = fork_child(processes, fprocesses)))
		return (-1);
	new_process->pc = index + processes->pc;
	ft_memcpy(parameters->arena + new_process->pc, new_process->code,
													new_process->code_size);
	*fprocesses = new_process;
	return (1);
}
