/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:12:11 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/12 12:57:55 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		lldi(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		index;
	int		sum;
	int		to_save;

	if (processes->args[2] > 0 && processes->args[2] < 17)
	{
		if (size[0] == 3)
			processes->args[0] = if_arg_tind(processes, parameters, 0);
		if (size[1] == 3)
			processes->args[1] = if_arg_tind(processes, parameters, 1);
		if ((parameters->verbos >> 2) & 1)
			printf("P %4d | lldi %d %d r%d\n", processes->id,
				processes->args[0], processes->args[1], processes->args[2]);
		if ((parameters->verbos >> 2) & 1)
			printf("       | -> load from %d + %d = %d (with pc %d)\n",
				processes->args[0], processes->args[1],
				processes->args[0] + processes->args[1], processes->pc +
				processes->args[0] + processes->args[1]);
		sum = processes->args[0] + processes->args[1];
		index = processes->pc;
		index = (index + ((sum + MEM_SIZE) % MEM_SIZE)) % MEM_SIZE;
		to_save = get_vfarena(parameters->arena, 4, index);
		processes->registeries[processes->args[2] - 1] = to_save;
		(to_save == 0) && (processes->carry = 1);
		(to_save != 0) && (processes->carry = 0);
	}
	return (1);
}
