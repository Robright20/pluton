/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:45:32 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/16 20:38:56 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			print_usage(void)
{
	ft_printf("Usage: ./corewar [-d N -v N | -n N <champion1.cor> <...>\n"
		" -a / --aff         : Prints output from \"aff\" (Default is to"
		"hide it)\n"
		" -d / --dump   N    : Dumps memory after N cycles then exits\n"
		" -v / --verbos N    : Verbosity levels, can be added together "
		"to enable several\n"
		"			- 0 : Show only essentials (introduction + "
		"the winner)\n"
		"			- 1 : Show lives\n"
		"			- 2 : Show cycles\n"
		"			- 4 : Show operations (Params are NOT litteral ...)\n"
		"			- 8 : Show deaths\n");
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
