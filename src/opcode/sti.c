/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:58:16 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/20 13:38:22 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int			if_arg_tind(t_cursor *processes, t_game_para *parameters, int i)
{
	int		index;
	int		value;

	index = (processes->pc + processes->args[i] % IDX_MOD) % MEM_SIZE;
	value = get_vfarena(parameters->arena, 4, index);
	return (value);
}

t_cursor	*if_size_isreg(t_cursor *processes, int *size)
{
	if (size[1] == 1)
		processes->args[1] = processes->registeries[processes->args[1] - 1];
	if (size[2] == 1)
		processes->args[2] = processes->registeries[processes->args[2] - 1];
	return (processes);
}

int			sti(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		index;
	int		sum;

	index = processes->pc;
	processes = if_size_isreg(processes, size);
	if (processes->args[0] > 0 && processes->args[0] < 17)
	{
		if (size[1] == 3)
			processes->args[1] = if_arg_tind(processes, parameters, 1);
		if ((parameters->verbos >> 2) & 1)
			ft_printf("P %4d | sti r%d %d %d\n", processes->id,
			processes->args[0], processes->args[1], processes->args[2]);
		sum = processes->args[1] + processes->args[2];
		index = (index + ((sum % IDX_MOD + MEM_SIZE) % MEM_SIZE)) % MEM_SIZE;
		if ((parameters->verbos >> 2) & 1)
			ft_printf("       | -> store to %d + %d = \
%d (with pc and mod %d)\n", processes->args[1], processes->args[2],
	processes->args[1] + processes->args[2], sum % IDX_MOD + processes->pc);
		ft_dprintf(g_viz_fd, "##new-data|%d|%d|%d\n", processes->id,
														index % MEM_SIZE, 4);
		cpy_toarena(processes->registeries[processes->args[0] - 1],
														&parameters, index, 4);
	}
	return (1);
}
