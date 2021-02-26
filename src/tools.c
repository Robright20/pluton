/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:31:54 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/26 14:58:10 by aalhaoui         ###   ########.fr       */
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
		idx = ((processes->opcode == 13 && processes->opcode == 15) ? IDX_MOD : MAX_INT);
		i = (pc + get_vfarena(processes, arena, 2, pc) % idx) % MEM_SIZE;
		n = 4;
	}
	while (i < pc + n)
	{
		value <<= 8;
		value |= (int)arena[i];
		i = (i + 1) % MEM_SIZE;
	}
	return (value);
}

int     get_args(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		pc;
	int		i;

	pc = processes->pc + 2;
	i = -1;
	while (++i < op_tab[processes->opcode].args_counter)
	{
		processes->args[i] = get_vfarena(processes, parameters->arena, size[i], pc);
		pc = (pc + 1) % MEM_SIZE;
	}
	return (1);
}
