/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:10:53 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/26 15:10:10 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		or(t_cursor *processes, t_game_para *parameters)
{
	int		result;

	if (processes->args[2] > 0 && processes->args[2] < 17)
	{
		result = processes->args[0] | processes->args[1];
		processes->registeries[processes->args[2] - 1] = result;
		(result == 0) && (processes->carry = 1);
		(result != 0) && (processes->carry = 0);
	}
	return (1);
}
