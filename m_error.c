/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:34:15 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 15:31:54 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_error(t_asmdata *data, t_head_lb labels, t_head *head)
{
	if (data->ln == 0)
		ft_printf("Empty file\n");
	else if (data->n != -1)
		ft_printf("Error: no Name!\n");
	else if (data->c != -1)
		ft_printf("Error: no Comment\n");
	else
		ft_printf("ERROR: Champ has no instructions!\n");
	if (data->name)
		free(data->name);
	if (data->comment)
		free(data->comment);
	if (labels.first != NULL)
		list_del_all_lb(&labels);
	if (head->first != NULL)
		list_del_all(head);
	free(data->file_name);
}

int		print_arg_error(t_node instr, t_asmdata *data, int j, int lb)
{
	data->error = 1;
	ft_printf("Error:	Instruction >>> %s\n\tArgument #%d >>> %s.\n",
		instr.data, j + 1, data->op_tb[j]);
	if (lb == 1)
		ft_printf("*Label not found\n");
	if (lb == 2)
		ft_printf("*Too few Arguments to operation call\n");
	if (lb == 3)
		ft_printf("*Too much Arguments to operation call\n");
	return (0);
}

int		print_oper_error(char *line, t_asmdata *data)
{
	data->error = 1;
	ft_printf("Error: Line >>> %s. Operation not found.\n", line);
	return (0);
}

int		cmp_nm_cm(char *line)
{
	if ((ft_strscmp(NAME_CMD_STRING, line, 0, 5) == 0))
		return (1);
	else if ((ft_strscmp(COMMENT_CMD_STRING, line, 0, 8) == 0))
		return (2);
	else
		return (0);
}

int		check_champion_name_comment(t_asmdata *data)
{
	if (data->comment && (ft_strlen(data->comment) > COMMENT_LENGTH))
	{
		ft_printf("Error: .comment too long (%d) > max len (%d)\n",
		ft_strlen(data->comment), COMMENT_LENGTH);
		free(data->comment);
		if (data->name)
			free(data->name);
		return (0);
	}
	if (data->name && (ft_strlen(data->name) > PROG_NAME_LENGTH))
	{
		ft_printf("Error: .name too long (%d) > max len (%d)\n",
		ft_strlen(data->name), PROG_NAME_LENGTH);
		free(data->name);
		if (data->comment)
			free(data->comment);
		return (0);
	}
	return (1);
}
