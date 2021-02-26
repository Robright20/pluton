/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:20:27 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/26 15:10:05 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int     lld(t_cursor *processes, t_game_para *parameters)
{
    if (processes->args[1] > 0 && processes->args[1] < 17)
	{
		processes->registeries[processes->args[1] - 1] = processes->args[0];
		(processes->args[0] == 0) && (processes->carry = 1);
		(processes->args[0] != 0) && (processes->carry = 0);
	}
	return (1);
}