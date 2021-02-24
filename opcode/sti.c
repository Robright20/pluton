/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:58:16 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/24 11:57:45 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

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
	int		i;

	i = pc;
	value = 0;
	if (n == 3)
	{
		pc = (pc + get_vfarena(processes, arena, 2, pc) % IDX_MOD) % MEM_SIZE;
		n = 4;
	}
	if (n == 1)
	{
		value = arena[pc];
		if (value >= 1 && value <= 16)
			value = processes->registeries[value - 1];
	}
	else
		while (i < pc + n)
		{
			value <<= 8;
			value |= (int)arena[i];
			i = (i + 1) % MEM_SIZE;
		}
	return (value);
}

int		sti(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		index;
	int		pc;
	int		sum;
	char	arg1;

	sum = 0;
	pc = processes->pc;
	pc = (pc + 1) % MEM_SIZE;
	arg1 = get_vfarena(processes, parameters->arena, size[0], pc);
	index = pc;
	pc = (pc + size[0]) % MEM_SIZE;
	sum += get_vfarena(processes, parameters->arena, size[1], pc);
	pc = (pc + size[1]) % MEM_SIZE;
	sum += get_vfarena(processes, parameters->arena, size[2], pc);
	index = (index + ((sum + MEM_SIZE) % MEM_SIZE) % IDX_MOD) % MEM_SIZE;
	parameters->arena[index] = arg1;
	printf("%d %d\n", pc, parameters->arena[index]);
	return (1);
}
