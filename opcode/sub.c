/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:59:11 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/24 16:01:58 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		add(t_cursor *processes, t_game_para *parameters, int *size)
{
    int		pc;
    int		arg3;
	int		sum;

	sum = 0;
	pc = processes->pc;
	pc = (pc + 1) % MEM_SIZE;
	sum += get_vfarena(processes, parameters->arena, size[0], pc);
	pc = (pc + size[0]) % MEM_SIZE;
	sum -= get_vfarena(processes, parameters->arena, size[1], pc);
	pc = (pc + size[1]) % MEM_SIZE;
	arg3 = parameters->arena[pc];
	if (arg3 > 0 && arg3 <= 16)
		processes->registeries[arg3 - 1] = sum;
	(sum == 0) && (processes->carry = 1);
	(sum != 0) && (processes->carry = 0);
	return (1);
}