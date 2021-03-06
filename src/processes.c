/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:16:11 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/06 22:56:58 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cursor		*add_process(t_cursor *processes, t_players *players, int id)
{
	t_cursor		*new_process;

	if (!(new_process = (t_cursor *)ft_memalloc(sizeof(t_cursor))))
		return (NULL);
	new_process->id = ++unique_id;
	new_process->registeries[0] = -(id + 1);
	new_process->pc = MEM_SIZE / players->number_of_players * (unique_id - 1);
	new_process->wait_cycle = -1;
	new_process->code_size = players->player[id]->size;
	new_process->player_id = id + 1;
	new_process->next = NULL;
	if (!processes)
		processes = new_process;
	else
		new_process->next = processes;
	return (new_process);
}

void		players_introduction(t_players *players)
{
	int		i;

	i = -1;
	printf("Introducing contestants...\n");
	while (++i < players->number_of_players)
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
							players->player[i]->size, players->player[i]->name,
												players->player[i]->comment);
}

t_cursor	*init_processes(t_players *players)
{
	t_cursor	*processes;
	int			i;

	i = -1;
	processes = NULL;
	unique_id = 0;
	while (++i < players->number_of_players)
		if (!(processes = add_process(processes, players, i)))
			return (NULL);
	return (processes);
}

t_cursor	*remove_process(t_cursor *process, t_cursor *processes,
													t_game_para *parameters)
{
	t_cursor	*cur;
	t_cursor	*tmp;

	cur = processes;
	while (cur)
	{
		tmp = cur->next;
		if (cur == process)
		{
			processes = tmp;
			ft_memdel((void **)&cur);
			break ;
		}
		else if (tmp == process)
		{
			cur->next = tmp->next;
			ft_memdel((void **)&tmp);
			break ;
		}
		cur = tmp;
	}
	printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
		process->id, parameters->cycle_counter - process->last_live,
		parameters->cycle_to_die);
	return (processes);
}
