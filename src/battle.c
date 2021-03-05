/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:12:50 by mac               #+#    #+#             */
/*   Updated: 2021/03/05 16:37:27 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		the_check(t_cursor *processes, t_game_para *parameters)
{
	int			diff_lives;
	t_cursor	*cur_process;

	diff_lives = parameters->live_counter - parameters->last_live_counter;
	parameters->check_counter++;
	cur_process = processes;
	while (cur_process)
	{
		if (parameters->cycle_counter - cur_process->last_live >
												parameters->cycle_to_die)
			exit (0);
		if (!processes)
			return (parameters->last_live);
		cur_process = cur_process->next;
	}
	if (diff_lives >= NBR_LIVE || parameters->check_counter % MAX_CHECKS == 0)
	{
		parameters->cycle_to_die -= CYCLE_DELTA;
		printf("Cycle to die is now %d\n", parameters->cycle_to_die);
		if (parameters->cycle_to_die <= 0)
			parameters->cycle_to_die = 1;
		parameters->check_counter = 0;
	}
	parameters->last_live_counter = parameters->live_counter;
	return (0);
}

int				operations(t_cursor *processes, t_game_para *parameters,
											t_cursor **fprocesses, int *size)
{
	int		ret;
	int		op;

	ret = 1;
	op = processes->opcode;
	(op == 1) && (ret = live(processes, parameters));
	(op == 2) && (ret = ld(processes));
	(op == 3) && (ret = st(processes, parameters, size));
	(op == 4) && (ret = add(processes));
	(op == 5) && (ret = sub(processes));
	(op == 6) && (ret = and(processes, size));
	(op == 7) && (ret = or(processes, size));
	(op == 8) && (ret = xor(processes, size));
	(op == 9) && (ret = zjmp(processes));
	(op == 10) && (ret = ldi(processes, parameters));
	(op == 11) && (ret = sti(processes, parameters));
	(op == 12) && (ret = ft_fork(processes, parameters, fprocesses));
	(op == 13) && (ret = lld(processes));
	(op == 14) && (ret = lldi(processes, parameters));
	(op == 15) && (ret = lfork(processes, parameters, fprocesses));
	// (op == 16) && aff(processes, parameters);
	return (ret);
}

void			execute_operations(t_cursor *processes, t_game_para *parameters,
														t_cursor **fprocesses)
{
	int		*size;
	int		args_size;
	int		pc;

	pc = processes->pc;
	size = NULL;
	if (op_tab[processes->opcode - 1].codage_byte)
		size = check_codage_byte(parameters->arena[pc + 1], processes->opcode);
	if (!op_tab[processes->opcode - 1].codage_byte || !size[3])
	{
		get_args(processes, parameters, size);
		operations(processes, parameters, fprocesses, size);	
	}
	if (op_tab[processes->opcode - 1].codage_byte)
	{
		args_size = (size[0] == 3 ? 2 : size[0]) + (size[1] == 3 ? 2 : size[1])
												+ (size[2] == 3 ? 2 : size[2]);
		args_size = (args_size + MEM_SIZE) % MEM_SIZE;
		processes->pc = (pc + 2 + args_size) % MEM_SIZE;
	}
	else if (processes->opcode != 9)
		processes->pc = (pc + 1 + (op_tab[processes->opcode - 1].dir_size ? 2 : 4))
																	% MEM_SIZE;
	else if (processes->opcode == 9 && !processes->carry)
		processes->pc = (pc + 3) %MEM_SIZE;
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

int			start_battle(t_cursor *processes, t_players *players)
{
	t_game_para		*parameters;
	int				cycle_to_check;
	// int		i;
	// int		j;

	if (!(parameters = init_game_parameters(players)))
		return (-1);
	while (processes && parameters->cycle_to_die > 0)
	{
		cycle_to_check = 0;
		while (++cycle_to_check <= parameters->cycle_to_die)
		{
			parameters->cycle_counter++;
			// if (parameters->cycle_counter == 1072)
			// {
			// 	i = -1;
			// 	j = 0;
			// 	while (++i < 4096)
			// 	{
			// 		j++;
			// 		printf("%02hhx ", parameters->arena[i]);
			// 		if (j == 32)
			// 		{
			// 			printf("\n");
			// 			j = 0;
			// 		}
			// 		if (i == 2047)
			// 		{
			// 			j = 0;
			// 			printf("\n\n---------------------\n\n");
			// 		}
			// 	}
			// }
			printf("It is now cycle %d\n", parameters->cycle_counter);
			processes_execution(&processes, parameters);
		}
		if (the_check(processes, parameters))
			break ;
	}
	printf("“Contestant %d, \"%s\", has won !\n", parameters->last_live,
							players->player[parameters->last_live]->name);
	ft_memdel((void **)&parameters->arena);
	ft_memdel((void **)&parameters);
	return (1);
}
