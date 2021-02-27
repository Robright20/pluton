/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:56:09 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/27 18:50:09 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cursor	*fork_child(t_cursor *processes, t_cursor *fprocesses)
{
	t_cursor		*new_process;
	int				i;

	i = -1;
	if (!(new_process = (t_cursor *)ft_memalloc(sizeof(t_cursor))))
		return (NULL);
	new_process->id = processes->id;
	while (++i < 16)
		new_process->registeries[i] = processes->registeries[i];
	new_process->carry = processes->carry;
	new_process->code = processes->code;
	new_process->code_size = processes->code_size;
	new_process->next = fprocesses;
	return (new_process);
}

int			ft_fork(t_cursor *processes, t_game_para *parameters,
														t_cursor *fprocesses)
{
	int			index;
	t_cursor	*new_processes;

	index = ((processes->args[0] + MEM_SIZE) % MEM_SIZE) % IDX_MOD;
	if (!(new_processes = fork_child(processes, fprocesses)))
		return (-1);
	new_processes->pc = index + processes->pc;
	ft_memcpy(parameters->arena + new_processes->pc, new_processes->code,
													new_processes->code_size);
	new_processes->wait_cycle = -1;
	execute_operations(new_processes, parameters, fprocesses);
	return (1);
}
