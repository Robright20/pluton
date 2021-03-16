/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_champ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:26:45 by mac               #+#    #+#             */
/*   Updated: 2021/03/16 17:08:37 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			check_header(t_players **players, int id, int fd)
{
	unsigned int	magic_header;
	int				ret;
	int				boool;

	boool = 1;
	if ((magic_header = convert_to_numfd(4, fd)) != COREWAR_EXEC_MAGIC)
		boool = -4;
	else if ((ret = read(fd, (*players)->player[id]->name,
											PROG_NAME_LENGTH)) != 128)
		boool = -1;
	else if (convert_to_numfd(4, fd) != 0)
		boool = -4;
	else if (((*players)->player[id]->size = convert_to_numfd(4, fd)) < 0 ||
				(*players)->player[id]->size > 682)
		boool = -3;
	return (boool);
}

int			check_champ_file(t_players *players, char *champ, int id)
{
	char			tmp;
	int				fd;
	int				ret;
	int				boool;

	tmp = 0;
	boool = 1;
	if ((fd = open(champ, O_RDONLY)) < 0)
	{
		perror("champ");
		return (-1);
	}
	if ((ret = check_header(&players, id, fd)) < 0)
		return (ret);
	if (read(fd, players->player[id]->comment, COMMENT_LENGTH) != 2048)
		boool = -1;
	else if (convert_to_numfd(4, fd) != 0)
		boool = -1;
	else if ((ret = read(fd, players->player[id]->code,
											players->player[id]->size)))
		if ((ret != players->player[id]->size) || read(fd, &tmp, 1))
			boool = -4;
	close(fd);
	return (boool);
}

int			extension(char *champ, int champ_len)
{
	char	*extension;

	extension = ft_strsub(champ, champ_len - 4, champ_len);
	if (ft_strequ(extension, ".cor"))
	{
		ft_memdel((void **)&extension);
		return (1);
	}
	return (0);
}

int			verify_champ(t_players *players, char *argv, int id)
{
	int		ret;
	int		champ_len;

	champ_len = ft_strlen(argv);
	if (champ_len <= 4 || !extension(argv, champ_len))
	{
		write(2, "ERROR : champion name not valid\n", 32);
		return (-1);
	}
	if ((ret = check_champ_file(players, argv, id)) < 0)
	{
		if (ret == -3)
			write(2, "Error - Code is too large (max 682 bytes)\n", 42);
		else if (ret == -2)
			write(2, "Error - Invalid file signature", 30);
		else if (ret == -4)
			write(2, "Error - Inconsistent number of instructions\n", 44);
		else
			write(2, "ERROR : champion file not valid\n", 32);
		return (-1);
	}
	return (1);
}
