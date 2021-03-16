/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:20:16 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/16 22:07:00 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			flag_n(int argc, char **argv, t_players *players, int **ids_av)
{
	int		id;
	int		i;

	i = 0;
	id = 0;
	while (++i < argc)
		if (ft_strequ(argv[i], "-n") && (id = ft_atoi(argv[++i])) >= 0)
		{
			if (id > 0 && id < 5 && (*ids_av)[id - 1])
			{
				write(2, "ERROR : id  already reseved\n", 28);
				return (-1);
			}
			if (id < 1 || id > 4)
			{
				write(2, "ERROR : flag -n not valid\n", 26);
				return (-1);
			}
			(*ids_av)[id - 1] = 1;
			players->player[id - 1]->id = id;
		}
	return (1);
}

int			read_players_tmp(char **argv, t_players **players, int **ids_av,
																	int i)
{
	int		j;

	j = 0;
	while ((*ids_av)[j])
		j++;
	(*players)->player[j]->id = j + 1;
	(*ids_av)[j] = 1;
	if (verify_champ((*players), argv[i], j) < 0)
		return (-1);
	(*players)->number_of_players++;
	return (1);
}

int			read_players(int argc, char **argv, t_players *players,
															int **ids_av)
{
	int		i;
	int		ret;
	int		tmp;

	i = 0;
	tmp = 1;
	if ((ret = flag_n(argc, argv, players, ids_av)) < 0)
		return (-1);
	while (++i < argc)
		if (ft_strequ(argv[i], "-n"))
		{
			ret = ft_atoi(argv[i + 1]) - 1;
			if (verify_champ(players, argv[i + 2], ret) < 0)
				return (-1);
			players->number_of_players++;
			i += 2;
		}
		else if (ft_strequ(argv[i], "-v") || ft_strequ(argv[i], "--verbos"))
			((players->verbos = ft_atoi(argv[++i])) == 0) && (tmp = -2);
		else if (ft_strequ(argv[i], "-d") || ft_strequ(argv[i], "--dump"))
			((players->dump = ft_atoi(argv[++i])) == 0) && (tmp = -2);
		else if (ft_strequ(argv[i], "-a") || ft_strequ(argv[i], "--aff"))
			players->aff = 1;
		else if (read_players_tmp(argv, &players, ids_av, i) < 0)
			return (-1);
	return (tmp);
}

t_players	*init_players(void)
{
	t_players	*players;
	int			indx;

	indx = -1;
	players = (t_players *)ft_memalloc(sizeof(t_players));
	players->player = (t_player **)ft_memalloc(sizeof(t_player *) * 4);
	if (!players || !players->player)
	{
		ft_printf("init players not finished");
		return (NULL);
	}
	while (++indx < 4)
	{
		players->player[indx] = (t_player *)malloc(sizeof(t_player));
		players->player[indx]->name = (char *)ft_memalloc(129);
		players->player[indx]->code = (char *)ft_memalloc(683);
		players->player[indx]->comment = (char *)ft_memalloc(2049);
		if (!players->player[indx] || !players->player[indx]->name ||
			!players->player[indx]->comment || !players->player[indx]->code)
		{
			ft_printf("init players not finished");
			return (NULL);
		}
	}
	return (players);
}

int			main(int argc, char **argv)
{
	t_players	*players;
	t_cursor	*processes;
	int			*ids_av;
	int			ret;

	processes = NULL;
	if (!(ids_av = (int *)ft_memalloc(sizeof(int) * 4)))
		return (0);
	(argc == 1) && print_usage();
	if (!(players = init_players()))
		return (0);
	if ((ret = read_players(argc, argv, players, &ids_av) )< 0)
	{
		if (ret == -2)
			ft_printf("ERROR : dump or verbos not valid\n");
		return (0);
	}
	if (!(processes = init_processes(players, ids_av)))
		return (0);
	players_introduction(players, ids_av);
	start_battle(processes, players, ids_av);
	free_resources(players, ids_av);
	return (0);
}
