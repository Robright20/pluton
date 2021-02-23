/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:55:51 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/22 16:09:40 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		live(t_cursor *processes, t_game_para *parameters)
{
	int		arg1_value;
	char	*arg1;

	arg1 = ft_strsub(parameters->arena, processes->pc, 4);
	arg1_value = convert_to_num(arg1, 4);
	processes->pc += 4;
	if (arg1_value == processes->registeries[0])
	{
		parameters->last_live = -processes->registeries[0];
		parameters->live_counter++;
	}
	return (1);
}
