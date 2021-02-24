/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:15:44 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/24 16:00:57 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ld(t_cursor *processes, t_game_para *parameters, int *size)
{
    int		pc;
	int		arg1;
	int		arg2;

	pc = processes->pc;
	pc = (pc + 1) % MEM_SIZE;
	arg1 = get_vfarena(processes, parameters->arena, size[0], pc);
	pc = (pc + size[0]) % MEM_SIZE;
	arg2 = parameters->arena[pc];
	if (arg2 > 0 && arg2 < 17)
	{
		processes->registeries[arg2 - 1] = arg1;
		(arg1 == 0) && (processes->carry = 1);
		(arg2 != 0) && (processes->carry = 0);
	}
	return (1);
}