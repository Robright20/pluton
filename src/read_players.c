/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:20:16 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/21 16:04:38 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int	convert_to_numfd(int size, int fd)
{
	unsigned char	*buffer;
	unsigned int	hex;
	int				i;

	i = -1;
	hex = 0;
	if (!(buffer = ft_memalloc(sizeof(unsigned char) * 4)))
		return (0);
	if (read(fd, buffer, size) < 0)
		return (-1);
	while (++i < size)
	{
		hex <<= 8;
		hex |= (unsigned int)buffer[i];
	}
	ft_strdel((char **)&buffer);
	return (hex);
}

int	convert_to_num(char *str, int size)
{
	int		hex;
	int		i;

	i = -1;
	hex = 0;
	while (++i < size)
	{
		hex <<= 8;
		hex |= (int)str[i];
	}
	return (hex);
}

int			flag_n(int argc, char **argv, t_players *players, int *ids_av)
{
	int		id;
	int		i;

	i = 0;
	id = 0;
	while (++i < argc)
		if (ft_strequ(argv[i], "-n") && (id = ft_atoi(argv[++i])))
		{
			if (id > 0 && id < 5 && ids_av[id - 1])
			{
				printf("ERROR : id  already reseved\n");
				return (-1);
			}
			++i;
			if (id > 0 && id < 5)
			{
				ids_av[id - 1] = 1;
				players->player[id - 1]->id = id;
				if ((verify_champ(players, argv[i], id - 1)) < 0)
					return (-1);
			}
		}
	return (1);
}

int			read_players(int argc, char **argv, t_players *players, int *ids_av)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (flag_n(argc, argv, players, ids_av) < 0)
		return (-1);
	while (++i < argc)
		if (ft_strequ(argv[i], "-n"))
			i += 2;
		else
		{
			while (ids_av[j])
				j++;
			players->player[j]->id = j + 1;
			ids_av[j] = 1;
			if (verify_champ(players, argv[i], j) < 0)
				return (-1);
			players->number_of_players++;
		}
	return (1);
}

t_players	*init_players(void)
{
	t_players	*players;
	int			indx;

	indx = -1;
	players = (t_players *)ft_memalloc(sizeof(t_players));
	players->player = (t_player **)ft_memalloc(sizeof(t_player *));
	if (!players || !players->player)
	{
		printf("init players not finished");
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
			printf("init players not finished");
			return (NULL);
		}
	}
	return (players);
}

int		main(int argc, char **argv)
{
	t_players	*players;
	t_cursor	*processes;
	int			*ids_av;

	processes = NULL;
	if (!(ids_av = (int *)ft_memalloc(sizeof(int) * 4)))
		return (0);
	if (!(players = init_players()) ||
						!read_players(argc, argv, players, ids_av))
		return (0);
	if (!(processes = init_processes(players)))
		return (0);
	players_introduction(players);
	start_battle(processes, players);
	return (0);
}
