/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:12:23 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/24 11:58:07 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		xor(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		pc;
	int		result;
	int		arg1;
	int		arg2;

	pc = processes->pc;
	pc = (pc + 1) % MEM_SIZE;
	arg1 = get_vfarena(processes, parameters->arena, size[0], pc);
	pc = (pc + size[0]) % MEM_SIZE;
	arg2 = get_vfarena(processes, parameters->arena, size[1], pc);
	pc = (pc + size[1]) % MEM_SIZE;
	result = arg1 ^ arg2;
	(result == 0) && (processes->carry = 1);
	processes->registeries[(int )parameters->arena[pc]] = result;
	return (1);
}
