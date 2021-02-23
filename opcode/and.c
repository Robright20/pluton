/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:20:53 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/19 16:44:28 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		and(t_cursor *processes, t_game_para *parameters)
{
	int		*size;
	char	*arg1;
	char	*arg2;
	char	*arg3;
	int		tab[2];

	if (!(size = check_codage_byte(parameters->arena[processes->pc++], 11)))
		return (-1);
	if (!(arg1 = cpy_farena(parameters->arena + processes->pc, size[0])))
		return (-2);
	processes->pc += size[0];
	if (!(arg1 = cpy_farena(parameters->arena + processes->pc, size[1])))
		return (-2);
	processes->pc += size[1];
	tab[0] = convert_to_num(arg1, size[0]);
	tab[1] = convert_to_num(arg2, size[1]);
	tab[0] &= tab[1];
	if (!tab[0])
		processes->carry = 1;
	else
		processes->carry = 0;
	return (1);
}
