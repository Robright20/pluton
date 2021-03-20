/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:56:09 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/20 13:21:27 by aalhaoui         ###   ########.fr       */
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
	new_process->id = ++g_unique_id;
	while (++i < 16)
		new_process->registeries[i] = processes->registeries[i];
	new_process->carry = processes->carry;
	new_process->code_size = processes->code_size;
	new_process->player_id = processes->player_id;
	new_process->last_live = processes->last_live;
	new_process->next = *fprocesses;
	return (new_process);
}

int			ft_fork(t_cursor *processes, t_game_para *parameters,
														t_cursor **fprocesses)
{
	int			index;
	t_cursor	*new_process;

	index = (((processes->args[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
	if (!(new_process = fork_child(processes, fprocesses)))
		return (-1);
	new_process->pc = (index + processes->pc) % MEM_SIZE;
	if ((parameters->verbos >> 2) & 1)
		ft_printf("P %4d | fork %d (%d)\n", processes->id,
	processes->args[0], (processes->args[0] % IDX_MOD) + processes->pc);
	new_process->opcode = parameters->arena[new_process->pc];
	if (new_process->opcode < 1 || new_process->opcode > 16)
		new_process->pc = (new_process->pc + 1) % MEM_SIZE;
	else
		new_process->wait_cycle =
			g_op_tab[new_process->opcode - 1].cycle_to_wait;
	*fprocesses = new_process;
	ft_dprintf(g_viz_fd, "##new-process|%d|%d|%d\n", -(new_process->player_id),
										new_process->id, new_process->pc);
	return (1);
}
