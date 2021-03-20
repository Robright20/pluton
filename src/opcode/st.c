/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:33:14 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/20 13:21:27 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		st(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		index;
	int		arg1;

	if (processes->args[0] > 0 && processes->args[0] < 17)
	{
		if ((parameters->verbos >> 2) & 1)
			ft_printf("P %4d | %s r%d %d\n", processes->id,
			g_op_tab[processes->opcode - 1].name, processes->args[0],
			processes->args[1]);
		arg1 = processes->registeries[processes->args[0] - 1];
		if (size[1] == 1 && processes->args[1] > 0 && processes->args[1] < 17)
			processes->registeries[processes->args[1] - 1] = arg1;
		else
		{
			index = (processes->pc + ((processes->args[1] % IDX_MOD + MEM_SIZE)
														% MEM_SIZE)) % MEM_SIZE;
			ft_dprintf(g_viz_fd, "##new-data|%d|%d|%d\n", processes->id, index
																% MEM_SIZE, 4);
			cpy_toarena(arg1, &parameters, index, 4);
		}
	}
	return (1);
}
