/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_champ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:26:45 by mac               #+#    #+#             */
/*   Updated: 2021/03/12 12:27:14 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_champ_file(t_players *players, char *champ, int id)
{
	unsigned int	magic_header;
	char			*tmp;
	int				fd;
	int				ret;

	tmp = NULL;
	if ((fd = open(champ, O_RDONLY)) < 0)
	{
		perror("champ");
		return (-1);
	}
	if ((magic_header = convert_to_numfd(4, fd)) != COREWAR_EXEC_MAGIC)
		return (-2);
	if ((ret = read(fd, players->player[id]->name, PROG_NAME_LENGTH)) != 128)
		return (-1);
	if (convert_to_numfd(4, fd) != 0)
		return (-4);
	if ((players->player[id]->size = convert_to_numfd(4, fd)) < 0 ||
				players->player[id]->size > 682)
		return (-3);
	if (read(fd, players->player[id]->comment, COMMENT_LENGTH) != 2048)
		return (-1);
	if (convert_to_numfd(4, fd) != 0)
		return (-1);
	if ((ret = read(fd, players->player[id]->code, players->player[id]->size)))
		if ((ret != players->player[id]->size) || read(fd, tmp, 1))
			return (-4);
	close(fd);
	return (1);
}

int			extension(char *champ, int champ_len)
{
	char	*extension;

	extension = ft_strsub(champ, champ_len - 4, champ_len);
	if (ft_strequ(extension, ".cor"))
		return (1);
	return (0);
}

int		verify_champ(t_players *players, char *argv, int id)
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
