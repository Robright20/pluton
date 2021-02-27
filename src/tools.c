/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:31:54 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/28 00:05:16 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		*check_codage_byte(int codage_byte, int op)
{
	int		*size;
	int		tmp;
	int		type;
	int		i;
	int		j;

	i = 4;
	j = 0;
	if (!(size = ft_memalloc(sizeof(int) * 4)))
		return (NULL);
	while (--i > 3 - op_tab[op - 1].args_counter)
	{
		tmp = codage_byte;
		tmp = (tmp >> (i * 2)) & 3;
		(tmp == 1) && (size[j] = 1);
		(tmp == 3) && (size[j] = 3);
		((tmp == 2) && op_tab[op - 1].dir_size) && (size[j] = 2);
		((tmp == 2) && !op_tab[op - 1].dir_size) && (size[j] = 4);
		type = op_tab[op - 1].args[j++];
		type = (tmp >> (tmp - 1)) & 1;
		if (type != 1)
			size[3] = -1;
	}
	return (size);
}

int		get_vfarena(t_cursor *processes, char *arena, int n, int pc)
{
	int		value;
	int		idx;
	int		i;

	i = pc;
	value = 0;
	if (n == 3)
	{
		idx = processes->opcode == 13 || processes->opcode == 15;
		idx = idx ? IDX_MOD : MAX_INT;
		i = (pc + get_vfarena(processes, arena, 2, pc) % idx) % MEM_SIZE;
		n = 4;
	}
	while (i < pc + n)
	{
		value <<= 8;
		value |= (int)arena[i];
		printf("%d %d\n", pc, arena[i]);
		i = (i + 1) % MEM_SIZE;
	}
	return (value);
}

int			get_args(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		pc;
	int		i;
	int		tmp;

	pc = processes->pc + (op_tab[processes->opcode - 1].codage_byte ? 2 : 1);
	i = -1;
	while (++i < op_tab[processes->opcode - 1].args_counter)
	{
		if (op_tab[processes->opcode - 1].codage_byte)
			tmp = size[i];
		else 
			tmp = op_tab[processes->opcode - 1].dir_size ? 2 : 4;
		processes->args[i] =
						get_vfarena(processes, parameters->arena, tmp, pc);
		if (op_tab[processes->opcode - 1].codage_byte)
			pc = (pc + size[i]) % MEM_SIZE;
	}
	return (1);
}

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
