/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:16:11 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/20 17:34:08 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cursor		*add_process(t_cursor *processes, t_players *players, int id)
{
	t_cursor		*new_process;

	if (!(new_process = (t_cursor *)ft_memalloc(sizeof(t_cursor))))
		return (NULL);
	new_process->id = ++g_unique_id;
	new_process->registeries[0] = -(id + 1);
	new_process->pc = MEM_SIZE / players->number_of_players * (g_unique_id - 1);
	new_process->wait_cycle = -1;
	new_process->code_size = players->player[id]->size;
	new_process->player_id = id + 1;
	new_process->next = NULL;
	if (!processes)
		processes = new_process;
	else
		new_process->next = processes;
	ft_dprintf(g_viz_fd, "##new-user|%d|%s|%s|%s|%d\n", -(id + 1),
					players->player[id]->name, players->player[id]->comment,
											"code", players->player[id]->size);
	ft_dprintf(g_viz_fd, "##new-process|%d|%d|%d\n", -(id + 1), g_unique_id,
															new_process->pc);
	return (new_process);
}

void			players_introduction(t_players *players, int *ids_av)
{
	int		i;

	i = -1;
	ft_printf("Introducing contestants...\n");
	while (++i < 4)
		if (ids_av[i] == 1)
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				i + 1, players->player[i]->size, players->player[i]->name,
												players->player[i]->comment);
}

t_cursor		*init_processes(t_players *players, int *ids_av)
{
	t_cursor	*processes;
	int			i;

	i = -1;
	processes = NULL;
	g_unique_id = 0;
	while (++i < 4)
		if (ids_av[i] == 1 && !(processes = add_process(processes, players, i)))
			return (NULL);
	return (processes);
}

t_cursor		*remove_process(t_cursor *process, t_cursor *processes,
													t_game_para *parameters)
{
	t_cursor	*cur;
	t_cursor	*tmp;

	cur = processes;
	if ((parameters->verbos >> 2) & 1)
	{
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
		process->id, parameters->cycle_counter - process->last_live,
		parameters->or_cycle_to_die);
		ft_dprintf(g_viz_fd, "##kill-process|%d\n", process->id);
	}
	while (cur)
	{
		tmp = cur->next;
		(cur == process) && (processes = tmp);
		if (cur == process)
			ft_memdel((void **)&cur);
		(tmp == process) && (cur->next = tmp->next);
		if (tmp == process)
			ft_memdel((void **)&tmp);
		if (tmp == process || cur == process)
			break ;
		cur = tmp;
	}
	return (processes);
}

void		check_processes(t_cursor **processes, t_game_para *parameters)
{
	t_cursor	*cur_process;
	t_cursor	*tmp;

	cur_process = (*processes);
	while (cur_process)
	{
		tmp = cur_process->next;
		if (parameters->cycle_counter - cur_process->last_live >=
													parameters->cycle_to_die)
		{
			ft_dprintf(g_viz_fd, "##kill-process|%d\n", cur_process->id);
			(*processes) = remove_process(cur_process, (*processes),
																parameters);
		}
		cur_process = tmp;
	}
}
