/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:58:16 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/22 16:48:14 by aalhaoui         ###   ########.fr       */
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
	if (!(size = ft_memalloc(sizeof(int) * 3)))
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
			return (NULL);
	}
	return (size);
}

int		get_vfarena(char *arena, int n, int pc)
{
	int		value;
	int		i;

	if (n == 3)
	{
		pc = get_vfarena(arena, 2, pc);
		n = 4;
	}
	i = pc;
	value = 0;
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
	arg1 = parameters->arena[pc];
	if (arg1 >= 1 && arg1 <= 16)
		arg1 = processes->registeries[arg1 - 1];
	else
		return (-1);
	index = pc;
	pc = (pc + 1) % MEM_SIZE;
	sum += get_vfarena(parameters->arena, size[1], pc);
	pc = (pc + size[1]) % MEM_SIZE;
	sum += get_vfarena(parameters->arena, size[2], pc);
	pc = (pc + size[2]) % MEM_SIZE;
	index = (index + ((sum + MEM_SIZE) % MEM_SIZE) % IDX_MOD) % MEM_SIZE;
	parameters->arena[index] = arg1;
	printf("%d %d\n", index, parameters->arena[index]);
	return (1);
}


// - read opration byte 
// - read types byte and validate it -> get size of arguments = NBR 
// - if valid -> exec operation + skip NBR bytes
// - if not -> skip NBR bytes

// regestries[0] = -2; // 11111111 11111111 11111111 11111110 -> ff ff ff fe (in macOs fe ff ff ff)
// // in the arene --> ff ff ff fe
							 
// get vfarena
// post vtarena
// check_reg_index

// red_argument_farena();