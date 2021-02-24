/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:55:51 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/24 14:29:57 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		live(t_cursor *processes, t_game_para *parameters)
{
	int		arg1;

	arg1 = get_vfarena(processes, parameters->arena, 4, processes->pc);
	if (arg1 == processes->registeries[1])
		parameters->last_live = arg1;
	processes->pc = (processes->pc + 4)	% MEM_SIZE;
	return (1);
}
