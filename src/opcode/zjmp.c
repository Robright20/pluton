/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:00:38 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/26 15:07:58 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		zjmp(t_cursor *processes, t_game_para *parameters)
{
	if (processes->carry)
		processes->pc = (processes->pc + processes->args[0] % IDX_MOD) % MEM_SIZE;
	return (1);
}