/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_champ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:26:45 by mac               #+#    #+#             */
/*   Updated: 2021/02/27 15:08:19 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_champ_file(t_players *players, char *champ, int id)
{
	unsigned int	magic_header;
	int				fd;
	int				ret;

	if ((fd = open(champ, O_RDONLY)) < 0)
	{
		perror("champ");
		return (-1);
	}
	if ((magic_header = convert_to_numfd(4, fd)) != COREWAR_EXEC_MAGIC)
		return (-1);
	if (read(fd, players->player[id]->name, PROG_NAME_LENGTH) != 128)
		return (-1);
	if (convert_to_numfd(4, fd) != 0)
		return (-1);
	if ((players->player[id]->size = convert_to_numfd(4, fd)) < 0)
		return (-1);
	if (read(fd, players->player[id]->comment, COMMENT_LENGTH) != 2048)
		return (-1);
	if (convert_to_numfd(4, fd) != 0)
		return (-1);
	if ((ret = read(fd, players->player[id]->code, players->player[id]->size))
				> 682 || ret < 0)
		return (-1);
	close(fd);
	return (1);
}

int		verify_champ(t_players *players, char *argv, int id)
{
	int		champ_len;
	char	*extension;

	champ_len = ft_strlen(argv);
	if (!(extension = ft_strsub(argv, champ_len - 4, champ_len)))
		return (-1);
	if (!ft_strequ(extension, ".cor"))
	{
		printf("ERROR : champion extension error");
		return (-1);
	}
	if (check_champ_file(players, argv, id) < 0)
	{
		printf("ERROR : champion file not valid");
		return (-1);
	}
	return (1);
}
