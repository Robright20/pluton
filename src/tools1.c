/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:45:32 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/13 11:47:01 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			print_usage(void)
{
	printf("Usage: ./corewar [-d N -v N | -n N <champion1.cor> <...>\n");
	printf(" -d / --dump   N    : Dumps memory after N cycles then exits\n");
	printf(" -v / --verbos N    : Verbosity levels, can be added together ");
	printf("to enable several\n");
	printf("			- 0 : Show only essentials (introduction + ");
	printf("the winner)\n");
	printf("			- 1 : Show lives\n");
	printf("			- 2 : Show cycles\n");
	printf("			- 4 : Show operations (Params are NOT litteral ...)\n");
	printf("			- 8 : Show deaths\n");
	return (1);
}

void		free_resources(t_players *players, int *ids_av)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		ft_memdel((void **)&players->player[i]->comment);
		ft_memdel((void **)&players->player[i]->name);
		ft_memdel((void **)&players->player[i]->code);
		ft_memdel((void **)&players->player[i]);
	}
	ft_memdel((void **)&players->player);
	ft_memdel((void **)&players);
	ft_memdel((void **)&ids_av);
}
