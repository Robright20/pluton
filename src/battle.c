/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:12:50 by mac               #+#    #+#             */
/*   Updated: 2021/02/26 15:28:20 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_game_para		*init_game_parameters(t_players *players)
{
	t_game_para *parameters;

	if (!(parameters = (t_game_para *)ft_memalloc(sizeof(t_game_para))))
		return (NULL);
	if (!init_arena(players, parameters))
		return (NULL);
	parameters->cycle_to_die = CYCLE_TO_DIE;
	parameters->opcode_wait_cycles[0] = 10;
	parameters->opcode_wait_cycles[1] = 5;
	parameters->opcode_wait_cycles[2] = 5;
	parameters->opcode_wait_cycles[3] = 10;
	parameters->opcode_wait_cycles[4] = 10;
	parameters->opcode_wait_cycles[5] = 6;
	parameters->opcode_wait_cycles[6] = 6;
	parameters->opcode_wait_cycles[7] = 6;
	parameters->opcode_wait_cycles[8] = 20;
	parameters->opcode_wait_cycles[9] = 25;
	parameters->opcode_wait_cycles[10] = 25;
	parameters->opcode_wait_cycles[11] = 800;
	parameters->opcode_wait_cycles[12] = 10;
	parameters->opcode_wait_cycles[13] = 50;
	parameters->opcode_wait_cycles[14] = 1000;
	parameters->opcode_wait_cycles[15] = 2;
	return (parameters);
}

void		execute_operation(t_cursor *processes, t_game_para *parameters, t_cursor *fprocesses)
{
	int		*size;

	if (op_tab[processes->opcode].codage_byte)
		size = check_codage_byte(parameters->arena[processes->pc + 1], processes->opcode);
	if (!op_tab[processes->opcode].codage_byte || !size[3])
	{
		get_args(processes, parameters, size);
		(processes->opcode == 1) && live(processes, parameters);
		(processes->opcode == 2) && ld(processes, parameters);
		(processes->opcode == 3) && st(processes, parameters);
		(processes->opcode == 4) && add(processes, parameters);
		(processes->opcode == 5) && sub(processes, parameters);
		(processes->opcode == 6) && and(processes, parameters);
		(processes->opcode == 7) && or(processes, parameters);
		(processes->opcode == 8) && xor(processes, parameters);
		(processes->opcode == 9) && zjmp(processes, parameters);
		(processes->opcode == 10) && ldi(processes, parameters);
		(processes->opcode == 11) && sti(processes, parameters);
		(processes->opcode == 12) && ft_fork(processes, parameters, fprocesses);
		(processes->opcode == 13) && lld(processes, parameters);
		(processes->opcode == 14) && lldi(processes, parameters);
		// (processes->opcode == 15) && lfork(processes, parameters, fprocesses);
		// (processes->opcode == 16) && aff(processes, parameters);
	}
	if (op_tab[processes->opcode].codage_byte)
		processes->pc = (processes->pc + 2 + (size[0] == 3 ? 2 : size[0]) +
		(size[1] == 3 ? 2 : size[1]) + (size[2] == 3 ? 2 : size[2])) % MEM_SIZE;
	else
		processes->pc = (processes->pc + (op_tab[processes->opcode].dir_size ? 2 : 4)) % MEM_SIZE;
	ft_memdel((void **)&size);
}

int			set_opcode(t_cursor *processes, t_game_para *parameters, t_cursor *fprocesses)
{
	printf("--->>>>>\n");
	if (processes->wait_cycle < 0)
	{
		processes->opcode = parameters->arena[processes->pc];
		processes->wait_cycle = 1;
	}
	processes->wait_cycle--;
	if (!processes->wait_cycle)
		execute_operation(processes, parameters, fprocesses);
	return (1);
}

int			processes_execution(t_cursor *processes, t_game_para *parameters)
{
	t_cursor	*cur_process;

	cur_process = processes;
	while (cur_process)
	{
		set_opcode(cur_process, parameters, processes);
		printf("%d\n", cur_process->registeries[0]);
		cur_process = cur_process->next;
		parameters->cycle_counter++;
	}
	return (1);
}

int			start_battle(t_cursor *processes, t_players *players)
{
	t_game_para		*parameters;
	int				cycle_to_check;

	cycle_to_check = 0;
	if (!(parameters = init_game_parameters(players)))
		return (-1);
	while (processes && parameters->cycle_to_die > 0)
		while (++cycle_to_check < parameters->cycle_to_die)
		{
			processes_execution(processes, parameters);
			exit(0);
		}
	return (1);
}
