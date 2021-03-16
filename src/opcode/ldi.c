/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:43:44 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/16 17:14:33 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ldi(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		index;
	int		sum;
	int		to_save;

	if (processes->args[2] > 0 && processes->args[2] < 17)
	{
		if (size[0] == 3)
			processes->args[0] = if_arg_tind(processes, parameters, 0);
		if ((parameters->verbos >> 2) & 1)
			ft_printf("P %4d | ldi %d %d r%d\n", processes->id,
				processes->args[0], processes->args[1], processes->args[2]);
		sum = processes->args[0] + processes->args[1];
		index = processes->pc;
		index = (index + ((sum % IDX_MOD + MEM_SIZE) % MEM_SIZE)) % MEM_SIZE;
		if ((parameters->verbos >> 2) & 1)
			ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\
			\n", processes->args[0], processes->args[1], sum, sum % IDX_MOD +
																processes->pc);
		to_save = get_vfarena(parameters->arena, 4, index);
		processes->registeries[processes->args[2] - 1] = to_save;
	}
	return (1);
}
