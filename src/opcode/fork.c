/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:56:09 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/26 16:33:41 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cursor     *fork_init_child(t_cursor *processes)
{
    t_cursor		*new_process;
	int				i;

	i = -1;
	if (!(new_process = (t_cursor *)ft_memalloc(sizeof(t_cursor))))
		return (NULL);
    new_process->id = processes->id;
	while (++i < 16)
		new_process->registeries[i] = processes->registeries[i];
	new_process->pc = processes->pc;
	new_process->carry = processes->carry;
	new_process->next = NULL;
}

int		ft_fork(t_cursor *processes, t_game_para *parameters, t_cursor *fprocesses)
{
    int			index;
    t_cursor	*new_processes;

    index = processes->pc + (processes->args[0] % IDX_MOD);
	new_processes = fork_init_child(processes);
    cpy_toarena(new_processes, index);
    return (1);
}
