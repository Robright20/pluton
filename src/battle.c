/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:12:50 by mac               #+#    #+#             */
/*   Updated: 2021/02/27 16:11:43 by aalhaoui         ###   ########.fr       */
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

int				operations(t_cursor *processes, t_game_para *parameters,
											t_cursor *fprocesses, int op)
{
	int		ret;

	ret = 1;
	(op == 1) && (ret = live(processes, parameters));
	(op == 2) && (ret = ld(processes, parameters));
	(op == 3) && (ret = st(processes, parameters));
	(op == 4) && (ret = add(processes, parameters));
	(op == 5) && (ret = sub(processes, parameters));
	(op == 6) && (ret = and(processes, parameters));
	(op == 7) && (ret = or(processes, parameters));
	(op == 8) && (ret = xor(processes, parameters));
	(op == 9) && (ret = zjmp(processes, parameters));
	(op == 10) && (ret = ldi(processes, parameters));
	(op == 11) && (ret = sti(processes, parameters));
	(op == 12) && (ret = ft_fork(processes, parameters, fprocesses));
	(op == 13) && (ret = lld(processes, parameters));
	(op == 14) && (ret = lldi(processes, parameters));
	(op == 15) && (ret = lfork(processes, parameters, fprocesses));
	// (op == 16) && aff(processes, parameters);
	return (ret);
}

void			execute_operations(t_cursor *processes, t_game_para *parameters,
														t_cursor *fprocesses)
{
	int		*size;
	int		args_size;
	int		pc;

	pc = processes->pc;
	if (op_tab[processes->opcode].codage_byte)
		size = check_codage_byte(parameters->arena[pc + 1], processes->opcode);
	if (!op_tab[processes->opcode].codage_byte || !size[3])
	{
		get_args(processes, parameters, processes->opcode);
		operations(processes, parameters, fprocesses, size);
	}
	if (op_tab[processes->opcode].codage_byte)
	{
		args_size = (size[0] == 3 ? 2 : size[0]) + (size[1] == 3 ? 2 : size[1])
												+ (size[2] == 3 ? 2 : size[2]);
		args_size = (args_size + MEM_SIZE) % MEM_SIZE;
		processes->pc = (pc + 2 + args_size) % MEM_SIZE;
	}
	else
		processes->pc = (pc + (op_tab[processes->opcode].dir_size ? 2 : 4))
																	% MEM_SIZE;
	processes->wait_cycle = -1;
	ft_memdel((void **)&size);
}

int			processes_execution(t_cursor *processes, t_game_para *parameters)
{
	t_cursor	*cur_process;

	cur_process = processes;
	while (cur_process)
	{
		if (cur_process->wait_cycle < 0)
		{
			cur_process->opcode = parameters->arena[cur_process->pc];
			cur_process->wait_cycle =
								op_tab[cur_process->opcode].cycle_to_wait;
		}
		cur_process->wait_cycle--;
		if (!cur_process->wait_cycle)
			execute_operations(cur_process, parameters, processes);
		cur_process = cur_process->next;
	}
	return (1);
}

int		the_check(t_cursor *processes, t_game_para *parameters)
{
	int			diff_lives;
	t_cursor	*cur_process;

	diff_lives = parameters->live_counter - parameters->last_live_counter;
	parameters->check_counter++;
	cur_process = processes;
	while (cur_process)
	{
		if (parameters->live_counter - processes->last_live >
												parameters->cycle_to_die)
			remove_process(processes);
		cur_process = cur_process->next;
	}
	if (diff_lives >= NBR_LIVE || parameters->check_counter % MAX_CHECKS == 0)
	{
		parameters->cycle_to_die -= CYCLE_DELTA;
		if (parameters->cycle_to_die <= 0)
			return (remove_all_processes(processes));
		parameters->check_counter = 0;
	}
	parameters->last_live_counter = parameters->live_counter;
	return (0);
}

int			start_battle(t_cursor *processes, t_players *players)
{
	t_game_para		*parameters;
	int				cycle_to_check;

	if (!(parameters = init_game_parameters(players)))
		return (-1);
	while (processes && parameters->cycle_to_die > 0)
	{
		cycle_to_check = 0;
		while (++cycle_to_check < parameters->cycle_to_die)
		{
			processes_execution(processes, parameters);
			parameters->cycle_counter++;
		}
		the_check(processes, parameters);
	}
	ft_memdel((void **)&parameters->arena);
	ft_memdel((void **)&parameters);
	return (1);
}
