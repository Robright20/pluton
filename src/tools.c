/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:31:54 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/08 18:27:17 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				*check_codage_byte(int codage_byte, int op)
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
		// printf("%d\n", size[j]);
		type = op_tab[op - 1].args[j++];
		(tmp == 1 | tmp == 2) && (type = (tmp >> (tmp - 1)) & 1);
		(tmp == 3) && (type = ((tmp >> 0 & 1) && (tmp >> 1 & 1)));
		if (type != 1)
			size[3] = -1;
	}
	return (size);
}

unsigned int	get_vfarena(char *arena, int n, int pc)
{
	unsigned int		value;
	int					i;
	int					end;

	i = pc % MEM_SIZE;
	value = 0;
	(n == 3) && (n = 2);
	end = pc + n;
	while (i < end)
	{
		value <<= 8;
		value = value | (unsigned char)arena[i];
		i = (i + 1) % MEM_SIZE;
		(i == 0) && (end %= MEM_SIZE);
	}
	(n == 2) && (value = (short)value);
	return (value);
}

int				get_args(t_cursor *processes, t_game_para *parameters,
																	int *size)
{
	int		pc;
	int		i;
	int		tmp;

	pc = (processes->pc + (op_tab[processes->opcode - 1].codage_byte ? 2 : 1))
																% MEM_SIZE;
	i = -1;
	while (++i < op_tab[processes->opcode - 1].args_counter)
	{
		if (op_tab[processes->opcode - 1].codage_byte)
			tmp = size[i];
		else
			tmp = op_tab[processes->opcode - 1].dir_size ? 2 : 4;
		processes->args[i] =
						get_vfarena(parameters->arena, tmp, pc);
		if (op_tab[processes->opcode - 1].codage_byte)
			pc = (pc + (size[i] == 3 ? 2 : size[i])) % MEM_SIZE;
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
	parameters->players = players;
	parameters->cycle_to_die = CYCLE_TO_DIE;
	parameters->or_cycle_to_die = parameters->cycle_to_die;
	parameters->last_live = players->number_of_players;
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

void			cpy_toarena(int reg, t_game_para **parameters, int index, int n)
{
	int		i;
	int		tmp;

	i = index % MEM_SIZE;
	index = index + n;
	tmp = (n - 1) * 8;
	while (i < index)
	{
		(*parameters)->arena[i] = (reg >> tmp) & 255;
		i = (i + 1) % MEM_SIZE;
		(i == 0) && (index %= MEM_SIZE);
		tmp -= 8;
	}
}
