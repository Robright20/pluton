/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:56:09 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/06 12:56:39 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cursor	*fork_child(t_cursor *processes, t_cursor **fprocesses)
{
	t_cursor		*new_process;
	int				i;

	i = -1;
	if (!(new_process = (t_cursor *)ft_memalloc(sizeof(t_cursor))))
		return (NULL);
	new_process->id = ++unique_id;
	while (++i < 16)
		new_process->registeries[i] = processes->registeries[i];
	new_process->carry = processes->carry;
	new_process->code_size = processes->code_size;
	new_process->player_id = processes->player_id;
	new_process->next = *fprocesses;
	return (new_process);
}

int			ft_fork(t_cursor *processes, t_game_para *parameters,
														t_cursor **fprocesses)
{
	int			index;
	t_cursor	*new_process;

	printf("P %4d | %s %d (%d)\n", processes->id,
		op_tab[processes->opcode - 1].name, processes->args[0],
										processes->pc + processes->args[0]);
	index = (((processes->args[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
	if (!(new_process = fork_child(processes, fprocesses)))
		return (-1);
	new_process->pc = (index + processes->pc) % MEM_SIZE;
	new_process->opcode = parameters->arena[new_process->pc];
	new_process->wait_cycle =
							op_tab[new_process->opcode - 1].cycle_to_wait;
	new_process->start = parameters->cycle_counter;
	*fprocesses = new_process;
	return (1);
}
