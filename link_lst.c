/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:30:54 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 15:31:00 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_node	*insert_node(t_head *head, void *data)
{
	t_node	*new_node;
	t_node	*p;

	new_node = ft_memalloc(sizeof(t_node));
	new_node->data = (data);
	new_node->next = NULL;
	new_node->position = head->l_size++;
	if (head->first == NULL)
		head->first = new_node;
	else
	{
		p = head->first;
		while (p->next != NULL)
			p = p->next;
		p->next = new_node;
	}
	if (new_node->position + 1 == head->l_size)
		return (new_node);
	return (NULL);
}

t_label	*insert_label(t_head_lb *head, void *data, int pos)
{
	t_label	*new_node;
	t_label	*p;

	new_node = ft_memalloc(sizeof(t_label));
	new_node->data = ft_strdup(data);
	new_node->size_ind = -1;
	new_node->operation_num = pos;
	new_node->next = NULL;
	new_node->position = head->l_size++;
	if (head->first == NULL)
		head->first = new_node;
	else
	{
		p = head->first;
		while (p->next != NULL)
			p = p->next;
		p->next = new_node;
	}
	if (new_node->position + 1 == head->l_size)
		return (new_node);
	return (NULL);
}

t_label	*search_by_name(t_label *l, char *x)
{
	if (l == NULL)
		return (NULL);
	if (!ft_strcmp(l->data, x))
		return (l);
	else
		return (search_by_name(l->next, x));
}

t_label	*search_by_pos(t_label *l, size_t x)
{
	if (l == NULL)
		return (NULL);
	if (l->operation_num == x)
		return (l);
	else
		return (search_by_pos(l->next, x));
}
