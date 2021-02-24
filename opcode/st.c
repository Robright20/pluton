/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:33:14 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/24 15:36:19 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		st(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		arg1;
	int		arg2;
	int		index;
	int		pc;
	
	pc = processes->pc;
	pc = (pc + 1) % MEM_SIZE;
	arg1 = get_vfarena(processes, parameters->arena, size[0], pc);
	pc = (pc + size[0]) % MEM_SIZE;
	arg2 = get_vfarena(processes, parameters->arena, size[1], pc);
	pc = (pc + size[1]) % MEM_SIZE;
	if (arg2 > 0 && arg2 <= 16 && size[1] == 1)
		processes->registeries[arg2] = arg1;
	if (size[1] != 1)
		parameters->arena[arg2] = arg1;
    return (1);
}
