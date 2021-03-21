/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_nc_encodin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:18:04 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 15:18:38 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			pars_chmp_nm_cm(t_asmdata *data, char *line)
{
	if (data->n == 1 && data->s && data->e && data->x == -1)
	{
		data->name = ft_strsub(line, data->s, data->e - data->s - 1);
		if (data->name)
			data->n = -1;
	}
	if (data->c == 1 && data->s && data->e && data->x == -1)
	{
		data->comment = ft_strsub(line, data->s, data->e - data->s - 1);
		if (data->comment)
			data->c = -1;
	}
	if (data->s && (data->c == 1 || data->n == 1))
	{
		data->x++;
		if (data->n == 1)
			return (join(line, data, &data->name, PROG_NAME_LENGTH));
		if (data->c == 1)
			return (join(line, data, &data->comment, COMMENT_LENGTH));
	}
	return (1);
}

int			join(char *line, t_asmdata *sdata, char **cmd, int v)
{
	char	*t;

	if (sdata->x == 0)
	{
		*cmd = ft_strcpy(ft_strnew(v), line + sdata->s);
		t = ft_strjoin(*cmd, "\n");
		free(*cmd);
		*cmd = t;
	}
	if (sdata->x > 0 && !sdata->e)
	{
		t = ft_strjoin(*cmd, line);
		free(*cmd);
		*cmd = ft_strjoin(t, "\n");
		free(t);
	}
	join_last_line(sdata, cmd, line);
	return (1);
}

void		join_last_line(t_asmdata *data, char **cmd, char *line)
{
	char	*tmp;
	char	*t;

	if (data->x > 0 && data->e)
	{
		tmp = ft_strnew(ft_strlen(line));
		t = ft_strjoin(*cmd, ft_strscpy(tmp, line, 0, data->e));
		free(*cmd);
		free(tmp);
		*cmd = t;
		data->x = -1;
		if (data->c == 1)
			data->c = -1;
		if (data->n == 1)
			data->n = -1;
	}
}

void		add_encodin_code(t_asmdata *sdata, t_node *instruct)
{
	sdata->x = 2;
	while (++sdata->x < 6)
	{
		if (sdata->x == 3)
			init_encodin_byte(instruct, sdata->x, 2 * sdata->x);
		if (sdata->x == 5)
			init_encodin_byte(instruct, sdata->x, sdata->x - 3);
		if (sdata->x == 4)
			init_encodin_byte(instruct, sdata->x, sdata->x);
	}
}

void		init_encodin_byte(t_node *instr, int p, int shift)
{
	if (instr->w_args[p] == REG_CODE)
		instr->encodin += REG_CODE << shift;
	if (instr->w_args[p] == DIR_CODE)
		instr->encodin += DIR_CODE << shift;
	if (instr->w_args[p] == IND_CODE)
		instr->encodin += IND_CODE << shift;
}
