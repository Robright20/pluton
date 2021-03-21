/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:09:12 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 15:14:15 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		reg_lexical_analysis(t_asmdata *data, t_node *instr, int y)
{
	if (!check_reg(data->op_tb[data->y], g_op_tab[y].args[data->y],
				instr, *data))
		return (print_arg_error(*instr, data, data->y, 0));
	instr->command_size += 1;
	instr->w_args[data->y] = T_REG;
	instr->w_args[data->y + 6] = 1;
	instr->w_args[data->y + 3] = REG_CODE;
	return (1);
}

int		dirl_lexical_analysis(t_asmdata *data, t_node *instr,
		t_head_lb labels, int y)
{
	int		x;

	x = data->z;
	if (!check_dir_lebel(x + 2 + data->op_tb[data->y],
			g_op_tab[y].args[data->y], labels))
		return (print_arg_error(*instr, data, data->y,
					((g_op_tab[y].args[data->y]) & T_DIR) > 0));
	else if (g_op_tab[y].dir_size == 0)
	{
		instr->command_size += DIR_SIZE;
		instr->w_args[data->y + 6] = DIR_SIZE;
	}
	else
	{
		instr->command_size += IND_SIZE;
		instr->w_args[data->y + 6] = IND_SIZE;
	}
	instr->w_args[data->y] = T_LAB + T_DIR;
	instr->w_args[data->y + 3] = DIR_CODE;
	if (data->y == 2)
		instr->lb += 4;
	else
		instr->lb += data->y + 1;
	return (1);
}

int		dir_lexical_analysis(t_asmdata *data, t_node *instr, int y)
{
	int	x;

	x = data->z;
	if (!check_dir(x + 1 + data->op_tb[data->y],
			g_op_tab[y].args[data->y], instr, *data))
		return (print_arg_error(*instr, data, data->y, 0));
	if (g_op_tab[y].dir_size == 0)
	{
		instr->command_size += DIR_SIZE;
		instr->w_args[data->y + 6] = DIR_SIZE;
	}
	else
	{
		instr->command_size += IND_SIZE;
		instr->w_args[data->y + 6] = IND_SIZE;
	}
	instr->w_args[data->y] = T_DIR;
	instr->w_args[data->y + 3] = DIR_CODE;
	return (1);
}

int		ind_lexical_analysis(t_asmdata *data, t_node *instr,
		t_head_lb labels, int y)
{
	if (data->op_tb[data->y][data->z] == '+'
			|| !(T_IND & g_op_tab[y].args[data->y]))
		return (print_arg_error(*instr, data, data->y, 0));
	if (check_digit(data->op_tb[data->y])
		&& !(ft_isalpha(data->op_tb[data->y][data->z + 1])))
	{
		instr->arg[data->y] = ft_atoi(data->op_tb[data->y]);
		instr->w_args[data->y + 6] = 2;
		instr->w_args[data->y] = T_IND;
		instr->w_args[data->y + 3] = IND_CODE;
		instr->command_size += IND_SIZE;
		return (1);
	}
	if (data->op_tb[data->y][data->z] == ':')
		return (ind_lb(data, labels, instr, y));
	return (1);
}

int		ind_lb(t_asmdata *data, t_head_lb labels, t_node *instr, int y)
{
	if (!check_ind(data->z + 1 + data->op_tb[data->y],
			g_op_tab[y].args[data->y], labels))
		return (print_arg_error(*instr, data, data->y,
				((g_op_tab[y].args[data->y]) & T_DIR)));
	else
	{
		instr->w_args[data->y + 6] = 2;
		instr->w_args[data->y] = T_IND + T_LAB;
		instr->w_args[data->y + 3] = IND_CODE;
		if (data->y == 2)
			instr->lb += 4;
		else
			instr->lb += data->y + 1;
		instr->command_size += IND_SIZE;
	}
	return (1);
}
