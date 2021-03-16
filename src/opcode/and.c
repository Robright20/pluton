/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:20:53 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/16 17:03:59 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		and(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		result;

	if (processes->args[2] > 0 && processes->args[2] < 17)
	{
		if (size[0] == 1)
			processes->args[0] = processes->registeries[processes->args[0] - 1];
		if (size[1] == 1)
			processes->args[1] = processes->registeries[processes->args[1] - 1];
		if (size[0] == 3)
			processes->args[0] = if_arg_tind(processes, parameters, 0);
		if (size[1] == 3)
			processes->args[1] = if_arg_tind(processes, parameters, 1);
		if ((parameters->verbos >> 2) & 1)
			ft_printf("P %4d | and %d %d r%d\n", processes->id,
			processes->args[0], processes->args[1], processes->args[2]);
		result = processes->args[0] & processes->args[1];
		processes->registeries[processes->args[2] - 1] = result;
		(result == 0) && (processes->carry = 1);
		(result != 0) && (processes->carry = 0);
	}
	return (1);
}
