/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:12:23 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/04 17:39:51 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		xor(t_cursor *processes, int *size)
{
	int		result;

	if (processes->args[2] > 0 && processes->args[2] < 17)
	{
		if (size[0] == 1)
			processes->args[0] = processes->registeries[processes->args[0] - 1];
		if (size[1] == 1)
			processes->args[1] = processes->registeries[processes->args[1] - 1];
		printf("P    %d | %s %d %d r%d\n", processes->player_id,
			op_tab[processes->opcode - 1].name, processes->args[0],
			processes->args[1], processes->args[2]);
		result = processes->args[0] ^ processes->args[1];
		processes->registeries[processes->args[2] - 1] = result;
		(result == 0) && (processes->carry = 1);
		(result != 0) && (processes->carry = 0);
	}
	return (1);
}
