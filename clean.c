/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:07:54 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 15:08:34 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	clean_data(t_asmdata *data, t_head_lb *labels, t_head *head)
{
	if (data->line)
		free(data->line);
	free(data->file_name);
	free(labels);
	free(head);
	free(data);
	exit(1);
}

void	*list_get(t_head *head)
{
	t_node	*l;
	char	*data;
	int		i;

	if (head->first == NULL)
		return (NULL);
	l = head->first;
	data = l->data;
	head->first = head->first->next;
	head->l_size--;
	i = -1;
	if (l->arg_tab)
	{
		while (l->arg_tab[++i])
			free(l->arg_tab[i]);
		free(l->arg_tab);
	}
	free(l->data);
	free(l);
	return (data);
}

void	*list_get_lb(t_head_lb *head)
{
	t_label		*l;
	char		*data;

	if (head->first == NULL)
		return (NULL);
	l = head->first;
	data = l->data;
	head->first = head->first->next;
	head->l_size--;
	free(l->data);
	free(l);
	return (data);
}

void	list_del_all(t_head *head)
{
	while (head->first != NULL)
		list_get(head);
}

void	list_del_all_lb(t_head_lb *head)
{
	while (head->first != NULL)
		list_get_lb(head);
}
