/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:55:51 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/24 12:17:14 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		live(t_cursor *processes, t_game_para *parameters, int size)
{
	int		arg1;

	arg1 = get_vfarena(processes, parameters->arena, 4, processes->pc);
	if (arg1 == processes->registeries[1])
		parameters->last_live;
	return (1);
}
