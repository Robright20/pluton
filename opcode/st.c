/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:33:14 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/25 19:24:40 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		st(t_cursor *processes, t_game_para *parameters, int *size)
{
	int		index;
	int		arg1;
	
	if (processes->args[0] > 0 && processes->args[0] < 17)
	{
		arg1 = processes->registeries[processes->args[0] - 1];
		if (size[1] == 1 && processes->args[1] > 0 && processes->args[1] < 17)
			processes->registeries[processes->args[1] - 1] = arg1;
		else
		{
			index = processes->pc + (processes->args[1] % IDX_MOD);
			parameters->arena[index] = arg1;
		}
	}
    return (1);
}
