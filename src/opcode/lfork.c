/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:51:44 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/27 14:55:17 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			lfork(t_cursor *processes, t_game_para *parameters,
														t_cursor *fprocesses)
{
	int			index;
	t_cursor	*new_processes;

	index = (processes->args[0] + MEM_SIZE) % MEM_SIZE;
	if (!(new_processes = fork_child(processes, fprocesses)))
		return (-1);
	new_processes->pc = index + processes->pc;
	ft_memcpy(parameters->arena + new_processes->pc, new_processes->code,
													new_processes->code_size);
	return (1);
}
