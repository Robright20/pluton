/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:00:38 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/27 19:04:23 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		zjmp(t_cursor *processes)
{
	int		index;

	if (processes->carry)
	{
		index = processes->pc + processes->args[0] % IDX_MOD;
		processes->pc = index % MEM_SIZE;
	}
	return (1);
}
