/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:15:44 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/10 17:20:37 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ld(t_cursor *processes, t_game_para *parameters, int *size)
{
	if (processes->args[1] > 0 && processes->args[1] < 17)
	{
		if (size[0] == 3)
			processes->args[0] = if_arg_tind(processes, parameters, 0);
		if ((parameters->verbos >> 2) & 1)
			printf("P %4d | ld %d r%d\n", processes->id, processes->args[0],
			processes->args[1]);
		processes->registeries[processes->args[1] - 1] = processes->args[0];
		(processes->args[0] == 0) && (processes->carry = 1);
		(processes->args[0] != 0) && (processes->carry = 0);
	}
	return (1);
}
