/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:20:09 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 15:29:26 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					reverse_endian(int i)
{
	unsigned char	c1;
	unsigned char	c2;
	unsigned char	c3;
	unsigned char	c4;

	c1 = i;
	c2 = i >> 8;
	c3 = i >> 16;
	c4 = i >> 24;
	return (((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4);
}

void				writ_args(t_asmdata *data, t_node *cmd, int fd)
{
	data->x = -1;
	while (++data->x < cmd->arg_num)
	{
		if (cmd->w_args[data->x + 6] == 2)
		{
			cmd->arg[data->x] = reverse_endian(cmd->arg[data->x] << 16);
			write(fd, &cmd->arg[data->x], cmd->w_args[data->x + 6]);
		}
		else if (cmd->w_args[data->x + 6] == 4)
		{
			cmd->arg[data->x] = reverse_endian(cmd->arg[data->x]);
			write(fd, &cmd->arg[data->x], cmd->w_args[data->x + 6]);
		}
		else
			write(fd, &cmd->arg[data->x], cmd->w_args[data->x + 6]);
	}
}

void				decode(t_asmdata *data, t_head *cmmnd, int fd)
{
	t_node			*cmd;

	cmd = cmmnd->first;
	while (cmd)
	{
		if (cmd->code > 0)
		{
			write(fd, &cmd->code, 1);
			if (cmd->encodin_code > 0)
				write(fd, &cmd->encodin, 1);
			writ_args(data, cmd, fd);
		}
		cmd = cmd->next;
	}
}

void				to_byte_code(t_head *head, t_asmdata *data)
{
	int				fp;
	int				jumper;
	long int		c;
	int				y;

	fp = open(data->file_name, O_CREAT | O_RDWR | O_TRUNC, 0600);
	jumper = -1;
	y = reverse_endian(COREWAR_EXEC_MAGIC);
	write(fp, &y, 4);
	jumper = -1;
	while (data->name[++jumper])
		write(fp, &data->name[jumper], 1);
	c = PROG_NAME_LENGTH - ft_strlen(data->name) + 4;
	lseek(fp, c * sizeof(char), SEEK_END);
	y = reverse_endian(head->code_size);
	write(fp, &y, 4);
	jumper = -1;
	while (data->comment[++jumper])
		write(fp, &data->comment[jumper], 1);
	c = COMMENT_LENGTH - ft_strlen(data->comment) + 4;
	lseek(fp, c * sizeof(char), SEEK_END);
	decode(data, head, fp);
	ft_printf("Succes Writing output program to %s\n", data->file_name);
	close(fp);
}
