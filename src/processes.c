/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:16:11 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/27 22:36:30 by mac              ###   ########.fr       */
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
		new_process->next = processes;
	return (new_process);
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
													players->player[i]->comment);
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

int		remove_process(t_cursor *process, t_cursor *processes)
{
	t_cursor	*cur;

	cur = processes;
	while (cur)
	{
		if (cur->next == process)
		{
			cur->next = process->next;
			ft_memdel((void **)&process);
			break ;
		}
		cur = cur->next;
	}
	return (1);
}

int		remove_all_processes(t_cursor *processes, t_game_para *parameters)
{
	t_cursor	*cur_process;
	t_cursor	*tmp;

	cur_process = processes;
	while (cur_process)
	{
		tmp = cur_process->next;
		ft_memdel((void **)&cur_process);
		cur_process = tmp;
	}
	return (parameters->last_live);
}
