/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:59:11 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/15 18:41:37 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		sub(t_cursor *processes, t_game_para *parameters)
{
	int		sum;

	if (processes->args[0] > 0 && processes->args[0] < 17 &&
		processes->args[1] > 0 && processes->args[1] < 17 &&
		processes->args[2] > 0 && processes->args[2] < 17)
	{
		if ((parameters->verbos >> 2) & 1)
			ft_printf("P %4d | %s r%d r%d r%d\n", processes->id,
			op_tab[processes->opcode - 1].name, processes->args[0],
			processes->args[1], processes->args[2]);
		processes->args[0] = processes->registeries[processes->args[0] - 1];
		processes->args[1] = processes->registeries[processes->args[1] - 1];
		sum = processes->args[0] - processes->args[1];
		processes->registeries[processes->args[2] - 1] = sum;
		(sum == 0) && (processes->carry = 1);
		(sum != 0) && (processes->carry = 0);
	}
	return (1);
}
