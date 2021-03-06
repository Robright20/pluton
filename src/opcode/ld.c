/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:15:44 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/06 12:56:38 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ld(t_cursor *processes)
{
	if (processes->args[1] > 0 && processes->args[1] < 17)
	{
		printf("P %4d | %s %d r%d\n", processes->id,
		op_tab[processes->opcode - 1].name, processes->args[0],
		processes->args[1]);
		processes->registeries[processes->args[1] - 1] = processes->args[0];
		(processes->args[0] == 0) && (processes->carry = 1);
		(processes->args[0] != 0) && (processes->carry = 0);
	}
	return (1);
}