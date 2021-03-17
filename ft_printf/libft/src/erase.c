/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 09:02:37 by mesafi            #+#    #+#             */
/*   Updated: 2021/03/17 10:21:43 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <deque.h>

void	erase(t_deque *deque)
{
	t_dlist	*node;

	while (deque->size != 0)
	{
		node = get_front(deque);
		free(node->content);
		free(node);
	}
}