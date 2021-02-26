/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:12:11 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/26 15:17:00 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int     lldi(t_cursor *processes, t_game_para *parameters)
{
    int		index;
    int		sum;
	int		to_save;

    if (processes->args[2] > 0 && processes->args[2] < 17)
    {
        sum = processes->args[0] + processes->args[1];
		index = (index + ((sum + MEM_SIZE) % MEM_SIZE)) % MEM_SIZE;
		to_save = get_vfarena(processes, init_arena, 4, index);
		processes->registeries[processes->args[2] - 1] = to_save;
    }
    return (1);
}