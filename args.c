/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:51:16 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 14:55:29 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			pars_args(t_node *instr, t_asmdata *data, int y, t_head_lb labels)
{
	int		c;
	char	*tmp;

	instr->arg_tab = ft_strsplit(data->x + instr->data, SEPARATOR_CHAR);
	data->op_tb = instr->arg_tab;
	c = 0;
	c = count_separator_char(instr->data, data);
	data->y = -1;
	while (data->op_tb[++data->y])
	{
		tmp = ft_strtrim(data->op_tb[data->y]);
		free(data->op_tb[data->y]);
		data->op_tb[data->y] = tmp;
		if (data->y == g_op_tab[y].args_numb && c + 1 > g_op_tab[y].args_numb)
			break ;
		if (!trt_arg(data, instr, labels, y))
			return (0);
	}
	if (data->y != g_op_tab[y].args_numb || c + 1 != g_op_tab[y].args_numb)
		return (print_arg_error(*instr,
					data, data->y, 2 + (c + 1 > g_op_tab[y].args_numb)));
	else
		instr->command_size += g_op_tab[y].encoding_code;
	return (1);
}

int			count_separator_char(char *line, t_asmdata *data)
{
	int		c;

	c = 0;
	while (line[++data->x])
		if (line[data->x] == SEPARATOR_CHAR)
			c++;
	return (c);
}

int			trt_arg(t_asmdata *data, t_node *instr, t_head_lb labels, int y)
{
	data->z = -1;
	if (ft_strlen(data->op_tb[data->y]) == 0)
		return (print_arg_error(*instr, data, data->y, 0));
	while (data->op_tb[data->y][++data->z])
	{
		if (data->op_tb[data->y][data->z] == 'r'
			&& ft_isdigit(data->op_tb[data->y][data->z + 1]))
			return (reg_lexical_analysis(data, instr, y));
		if (data->op_tb[data->y][data->z] == 'r'
			&& !ft_isdigit(data->op_tb[data->y][data->z + 1]))
			return (0);
		else if (data->op_tb[data->y][data->z] == '%'
			&& data->op_tb[data->y][data->z + 1] == ':')
			return (dirl_lexical_analysis(data, instr, labels, y));
		else if (data->op_tb[data->y][data->z] == '%')
			return (dir_lexical_analysis(data, instr, y));
		else if (data->op_tb[data->y][data->z] == '+'
				|| check_digit(data->op_tb[data->y])
				|| data->op_tb[data->y][data->z] == ':')
			return (ind_lexical_analysis(data, instr, labels, y));
		else
			return (print_arg_error(*instr, data, data->y, 0));
	}
	return (1);
}

int			check_isdigit(char *tmp, int j)
{
	int		i;

	i = 0;
	while (i <= j)
	{
		if (ft_isdigit(tmp[i]) || tmp[i] == 95
			|| (tmp[i] >= 97 && tmp[i] <= 122))
			i++;
		else
			break ;
	}
	return (i);
}
