/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:16:11 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/27 14:50:10 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cursor		*add_process(t_cursor *processes, t_players *players, int id)
{
	t_cursor		*new_process;
	static	int		unique_id;

	if (!(new_process = (t_cursor *)ft_memalloc(sizeof(t_cursor))))
		return (NULL);
	new_process->id = ++unique_id;
	new_process->registeries[0] = -(id + 1);
	new_process->pc = MEM_SIZE / players->number_of_players * (unique_id - 1);
	new_process->wait_cycle = -1;
	new_process->code = players->player[id]->code;
	new_process->code_size = players->player[id]->size;
	new_process->next = NULL;
	if (!processes)
		processes = new_process;
	else
		processes->next = new_process;
	return (processes);
}

void	delete_process(t_cursor *processes, int id)
{
	t_cursor	*tmp;
	t_cursor	*prev;

	tmp = processes;
	while (tmp)
	{
		if (processes->id == id)
		{
			prev->next = tmp->next;
			ft_memdel((void **)&tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void		players_introduction(t_players *players)
{
	int		i;

	i = -1;
	printf("Introducing contestants...\n");
	while (++i < players->number_of_players)
		printf("* player %d, weighing %d bytes, \"%s\",  (\"%s\") !\n", i + 1,
							players->player[i]->size, players->player[i]->name,
													players->player[i]->name);
}

t_cursor	*init_processes(t_players *players)
{
	t_cursor	*processes;
	int			i;

	i = -1;
	processes = NULL;
	while (++i < players->number_of_players)
		if (!(processes = add_process(processes, players, i)))
			return (NULL);
	return (processes);
}