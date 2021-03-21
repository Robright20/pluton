/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args_lbl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:36:01 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 15:36:17 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				save_labels_and_commands(t_head_lb *labels, char *line,
		t_head *head, t_asmdata *data)
{
	char		*tmp;
	static int	tmp_post;
	t_node		marker;

	data->s = search_forlbl_char(line, &tmp);
	if (data->s == check_isdigit(tmp, data->s) && ft_strlen(line) > data->s)
	{
		if (ft_strlen(line) > data->s + 1)
		{
			marker = *insert_node(head, ft_strtrim(data->s + 1 + line));
			insert_label(labels, tmp, tmp_post);
			tmp_post = marker.position + 1;
		}
		else
			insert_label(labels, tmp, tmp_post);
		free(tmp);
		free(line);
		return (1);
	}
	free(tmp);
	marker = *insert_node(head, line);
	tmp_post = marker.position + 1;
	return (1);
}

void			assembly_to_bytecode(t_head *head, t_asmdata *data,
		t_head_lb *labels)
{
	if (!pars_instructions(head, *labels, data)
		|| !set_label_args(head, *labels, data))
	{
		if (data->error & 16)
			ft_printf("ERRORR\n");
	}
	if (head->code_size != 0 && data->error == 0)
		to_byte_code(head, data);
	free(data->name);
	free(data->comment);
	if (labels->first != NULL)
		list_del_all_lb(labels);
	if (head->first != NULL)
		list_del_all(head);
	free(data->file_name);
}

int				set_label_args(t_head *head, t_head_lb labels, t_asmdata *data)
{
	t_label		*l;
	t_node		*instru;
	int			counter;

	instru = head->first;
	l = labels.first;
	counter = 0;
	while (instru)
	{
		if (instru->lb > 0 &&
				!get_labels_value(l, instru, labels.first, counter))
		{
			data->error += 16;
			return (0);
		}
		counter += instru->command_size;
		data->y = 0;
		instru = instru->next;
	}
	return (1);
}

int				get_labels_value(t_label *l, t_node *instru,
		t_label *first, int counter)
{
	int			jumper;

	l = NULL;
	jumper = -1;
	while (++jumper < instru->arg_num)
	{
		if ((instru->lb & jumper + 1 && jumper != 2)
			|| (instru->lb & 4 && jumper == 2))
		{
			l = search_by_name(first,
					1 + ft_strchr(instru->arg_tab[jumper], LABEL_CHAR));
			if (l)
			{
				if (l->size_ind == -1)
				{
					ft_printf("Error: label '%s' points to nothing.\n",
							l->data);
					return (0);
				}
				instru->arg[jumper] = l->size_ind - counter;
			}
		}
	}
	return (1);
}

int				search_forlbl_char(char *line, char **tmp)
{
	int			j;

	j = -1;
	while (line[++j])
		if (line[j] == LABEL_CHAR)
			break ;
	*tmp = ft_strncpy(ft_strnew(j), line, j);
	return (j);
}
