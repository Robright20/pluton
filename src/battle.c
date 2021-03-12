/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:53:28 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/12 16:46:35 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cursor	*the_check(t_cursor *processes, t_game_para *parameters)
{
	t_cursor	*cur_process;
	t_cursor	*tmp;

	parameters->check_counter++;
	cur_process = processes;
	while (cur_process)
	{
		tmp = cur_process->next;
		if (parameters->cycle_counter - cur_process->last_live >=
													parameters->cycle_to_die)
			processes = remove_process(cur_process, processes, parameters);
		cur_process = tmp;
	}
	if (parameters->live_counter - parameters->last_live_counter >= NBR_LIVE
								|| parameters->check_counter % MAX_CHECKS == 0)
	{
		parameters->cycle_to_die -= CYCLE_DELTA;
		if ((parameters->verbos >> 1) & 1)
			printf("Cycle to die is now %d\n", parameters->cycle_to_die);
		parameters->or_cycle_to_die = parameters->cycle_to_die;
		(parameters->cycle_to_die <= 0) && (parameters->cycle_to_die = 1);
		parameters->check_counter = 0;
	}
	parameters->last_live_counter = parameters->live_counter;
	return (processes);
}

int			operations(t_cursor *processes, t_game_para *parameters,
											t_cursor **fprocesses, int *size)
{
	int		ret;
	int		op;

	ret = 1;
	op = processes->opcode;
	(op == 1) && (ret = live(processes, parameters));
	(op == 2) && (ret = ld(processes, parameters, size));
	(op == 3) && (ret = st(processes, parameters, size));
	(op == 4) && (ret = add(processes, parameters));
	(op == 5) && (ret = sub(processes, parameters));
	(op == 6) && (ret = and(processes, parameters, size));
	(op == 7) && (ret = or(processes, parameters, size));
	(op == 8) && (ret = xor(processes, parameters, size));
	(op == 9) && (ret = zjmp(processes, parameters));
	(op == 10) && (ret = ldi(processes, parameters, size));
	(op == 11) && (ret = sti(processes, parameters, size));
	(op == 12) && (ret = ft_fork(processes, parameters, fprocesses));
	(op == 13) && (ret = lld(processes, parameters, size));
	(op == 14) && (ret = lldi(processes, parameters, size));
	(op == 15) && (ret = lfork(processes, parameters, fprocesses));
	// if (op == 16)
	// 	printf("%d\n", processes->registeries[(processes->args[0] - 1)] % 256);
	return (ret);
}

void		execute_operations(t_cursor *processes, t_game_para *parameters,
														t_cursor **fprocesses)
{
	int		*size;
	int		args_size;
	int		pc;

	pc = processes->pc % MEM_SIZE;
	size = NULL;
	if (op_tab[processes->opcode - 1].codage_byte)
		size = check_codage_byte(parameters->arena[pc + 1], processes->opcode);
	if (!op_tab[processes->opcode - 1].codage_byte || !size[3])
		get_args(processes, parameters, size);
	if (!op_tab[processes->opcode - 1].codage_byte || !size[3])
		operations(processes, parameters, fprocesses, size);
	if (op_tab[processes->opcode - 1].codage_byte)
	{
		args_size = (size[0] == 3 ? 2 : size[0]) + (size[1] == 3 ? 2 : size[1])
												+ (size[2] == 3 ? 2 : size[2]);
		args_size = (args_size + MEM_SIZE) % MEM_SIZE;
		processes->pc = (pc + 2 + args_size) % MEM_SIZE;
	}
	else if (processes->opcode != 9 ||
								(processes->opcode == 9 && !processes->carry))
		processes->pc = (pc + 1 + (op_tab[processes->opcode - 1].dir_size
														? 2 : 4)) % MEM_SIZE;
	processes->wait_cycle = -1;
	ft_memdel((void **)&size);
}

int			processes_execution(t_cursor **processes, t_game_para *parameters)
{
	t_cursor	*cur_process;

	cur_process = *processes;
	while (cur_process)
	{
		if (cur_process->wait_cycle < 0)
		{
			cur_process->opcode = parameters->arena[cur_process->pc];
			if (cur_process->opcode < 1 || cur_process->opcode > 16)
				cur_process->pc = (cur_process->pc + 1) % MEM_SIZE;
			else
				cur_process->wait_cycle =
								op_tab[cur_process->opcode - 1].cycle_to_wait;
		}
		cur_process->wait_cycle--;
		if (!cur_process->wait_cycle)
			execute_operations(cur_process, parameters, processes);
		cur_process = cur_process->next;
	}
	return (1);
}

int			start_battle(t_cursor *processes, t_players *players,
														int *ids_av)
{
	t_game_para		*parameters;
	int				cycle_to_check;

	if (!(parameters = init_game_parameters(players, ids_av)))
		return (-1);
	while (processes && parameters->cycle_to_die > 0)
	{
		cycle_to_check = 0;
		while (++cycle_to_check <= parameters->cycle_to_die)
		{
			parameters->cycle_counter++;
			if (parameters->cycle_counter == parameters->dump)
				return (dump_arena(parameters));
			if ((parameters->verbos >> 1) & 1)
				printf("It is now cycle %d\n", parameters->cycle_counter);
			processes_execution(&processes, parameters);
		}
		processes = the_check(processes, parameters);
	}
	printf("Contestant %d, \"%s\", has won !\n", parameters->last_live,
							players->player[parameters->last_live - 1]->name);
	ft_memdel((void **)&parameters->arena);
	ft_memdel((void **)&parameters);
	return (1);
}
