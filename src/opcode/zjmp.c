/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:00:38 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/09 23:28:04 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		zjmp(t_cursor *processes, t_game_para *parameters)
{
	int		index;

	if ((parameters->verbos >> 2) & 1)
		printf("P %4d | %s %d", processes->id,
		op_tab[processes->opcode - 1].name, processes->args[0]);
	if (processes->carry)
	{
		index = processes->pc + processes->args[0] % IDX_MOD;
		processes->pc = (index + MEM_SIZE) % MEM_SIZE;
		if ((parameters->verbos >> 2) & 1)
			printf(" OK\n");
	}
	else if ((parameters->verbos >> 2) & 1)
		printf(" FAILED\n");
	return (1);
}
