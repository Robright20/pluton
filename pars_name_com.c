/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_name_com.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:40:32 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 15:40:36 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			check_champion(char *line, t_asmdata *sdata)
{
	int		j;
	char	*tmp;

	j = -1;
	j = search_for_exention(line, sdata, j);
	if (sdata->n != 1 && sdata->c != 1)
		return (1);
	while (line[++j])
	{
		if (line[j] != ' ' && line[j] != '\t'
			&& line[j] != '"' && sdata->x == -1 && !sdata->s)
			return (0);
		if (line[j] == '"' && sdata->s && !sdata->e)
			sdata->e = j + 1;
		if (line[j] == '"' && !sdata->s)
			sdata->s = j + 1;
	}
	tmp = avoid_comment(ft_strtrim(sdata->e + line));
	j = ft_strlen(tmp);
	free(tmp);
	if (sdata->e > 0 && (sdata->n == 1 || sdata->c == 1) && j != 0)
		return (0);
	return (pars_chmp_nm_cm(sdata, line));
}

int			search_for_exention(char *line, t_asmdata *data, int j)
{
	while (line[++j])
		if (line[j] != ' ' && line[j] != '\t')
			break ;
	if (line[j] == '.')
		if (cmp_nm_cm(j + line) > 0)
		{
			if (data->s && !data->e)
				return (-1);
			data->e = 0;
			data->s = 0;
			data->x = -1;
			return (set_jumper(data, line, j));
		}
	return (-1);
}

int			set_jumper(t_asmdata *data, char *line, int j)
{
	if ((cmp_nm_cm(j + line) == 1 && data->n == -1)
		|| (cmp_nm_cm(j + line) == 2 && data->c == -1))
		return (-2);
	if (cmp_nm_cm(j + line) == 1)
		data->n = 1;
	if (cmp_nm_cm(j + line) == 2)
		data->c = 1;
	if (data->n == 1)
		j += 4;
	if (data->c == 1)
		j += 7;
	return (j);
}

char		*avoid_comment(char *line)
{
	int		i;
	char	*str;

	i = -1;
	while (line[++i])
		if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT_CHAR)
		{
			str = ft_strncpy(ft_strnew(i), line, i);
			free(line);
			return (str);
		}
	return (line);
}
