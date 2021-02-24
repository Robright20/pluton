/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:43:44 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/24 16:00:08 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ldi(t_cursor *processes, t_game_para *parameters, int *size)
{
    int		pc;
    int     index;
    int     sum;
	int 	arg3;
    
    sum = 0;
    pc = processes->pc;
    index = pc;
	pc = (pc + 1) % MEM_SIZE;
    sum += get_vfarena(processes, parameters->arena, size[0], pc);
	pc = (pc + size[0]) % MEM_SIZE;
    sum += get_vfarena(processes, parameters->arena, size[1], pc);
    pc = (pc + size[1]) % MEM_SIZE;
    arg3 = parameters->arena[pc];
    index = (index + ((sum + MEM_SIZE) % MEM_SIZE) % IDX_MOD) % MEM_SIZE;
    if (arg3 > 0 && arg3 < 17)
        processes->registeries[arg3 - 1] = 
                        get_vfarena(processes, parameters->arena, 4, index);
    return (1);
}