/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:55:51 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/16 18:18:41 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		live(t_cursor *processes, t_game_para *parameters)
{
	if ((parameters->verbos >> 2) & 1)
		ft_printf("P %4d | %s %d\n", processes->id,
			g_op_tab[processes->opcode - 1].name, processes->args[0]);
	parameters->live_counter++;
	processes->last_live = parameters->cycle_counter;
	if (processes->args[0] < 0 && processes->args[0] > -5)
	{
		if (parameters->verbos & 1)
			ft_printf("Player %d (%s) is said to be alive\n",
			-processes->args[0],
			parameters->players->player[-processes->args[0] - 1]->name);
		ft_dprintf(g_viz_fd, "##live|%d|%d\n", processes->id, processes->args[0]);
		parameters->last_live = -processes->args[0];
	}
	return (1);
}
