/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:12:50 by mac               #+#    #+#             */
/*   Updated: 2021/02/22 16:46:20 by aalhaoui         ###   ########.fr       */
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

int		execute_operation(t_cursor *processes, t_game_para *parameters)
{
	int 	ret;
	int		*size;

	ret = 1;
	if (!(size = check_codage_byte(parameters->arena[processes->pc], 11)))
		return (-1);
	printf("%d %d %d\n", size[0], size[1], size[2]);
	// (processes->opcode == 1) && (ret = live(processes, parameters));
	// (processes->opcode == 2) && (ret = ld(processes, parameters));
	// (processes->opcode == 3) && (ret = st(processes, parameters));
	// (processes->opcode == 4) && (ret = add(processes, parameters));
	// (processes->opcode == 5) && (ret = sub(processes, parameters));
	// (processes->opcode == 6) && (ret = and(processes, parameters));
	// (processes->opcode == 7) && (ret = or(processes, parameters));
	// (processes->opcode == 8) && (ret = xor(processes, parameters));
	// (processes->opcode == 9) && (ret = zjmp(processes, parameters));
	// (processes->opcode == 10) && (ret = ldi(processes, parameters));
	(processes->opcode == 11) && (ret = sti(processes, parameters, size));
	// (processes->opcode == 12) && (ret = ft_fork(processes, parameters));
	// (processes->opcode == 13) && (ret = lld(processes, parameters));
	// (processes->opcode == 14) && (ret = lldi(processes, parameters));
	// (processes->opcode == 15) && (ret = lfork(processes, parameters));
	// (processes->opcode == 16) && (ret = aff(processes, parameters));
	processes->pc = (processes->pc + size[0] + size[1] + size[2]) % MEM_SIZE;
	ft_memdel((void **)&size);
	return (ret);
}

int			set_opcode(t_cursor *processes, t_game_para *parameters)
{
	printf("--->>>>>\n");
	if (processes->wait_cycle < 0)
	{
		processes->opcode = parameters->arena[processes->pc];
		processes->pc = (processes->pc + 1) % MEM_SIZE;
		processes->wait_cycle = 1;
	}
	processes->wait_cycle--;
	if (!processes->wait_cycle)
		if (!execute_operation(processes, parameters))
			return (-1);
	return (1);
}

int			processes_execution(t_cursor *processes, t_game_para *parameters)
{
	t_cursor	*cur_process;

	cur_process = processes;
	while (cur_process)
	{
		if (cur_process->wait_cycle < 0)
			set_opcode(cur_process, parameters);
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
