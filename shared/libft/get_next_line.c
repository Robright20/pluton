/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bob <bob@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:21:04 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/17 11:01:43 by bob              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	The get_next_line function reads a line from a file descriptor(fd), deli-
**	mited by '\n'.
**	The caller provides a pointer's address(**line). A buffer will be
**	allocated and used to try to read a line ending with '\n'. Or it will
**	be reallocated otherwise.
**
**	Returns: 1 is a line was read, 0 if reach EOF and -1 if
**		-  (fd < 0 || BUFF_SIZE < 0 || fd > FD_MAX || line == NULL)
**		- read has failed
**
**	Bugs: always free the space *line coz it's always allocated.
*/

int				get_next_line(const int fd, char **line)
{
	static t_buffer	prev[MAX_FD];
	t_buffer		cur;
	int				ret;

	if (read(fd, NULL, 0) != 0 || BUFF_SIZE < 0 || !line)
		return (-1);
	buf_set(&cur, NULL, 0, 0);
	while (1)
	{
		if (!prev[fd].ptr)
		{
			*line = (char*)buf_realloc(&cur, cur.size + BUFF_SIZE);
			if ((ret = read(fd, *line + cur.size, BUFF_SIZE)) <= 0)
				return (ret == 0 ? (cur.size > 0) : ret);
			cur.size += ret;
		}
		else if (!buf_set(&cur, prev[fd].ptr, prev[fd].size, 0))
			buf_set(prev + fd, NULL, 0, 0);
		*line = (char*)cur.ptr;
		if ((cur.pos = index_of(cur.ptr, '\n', cur.size)) >= 0)
			return (((*line)[cur.pos] = '\0') || \
				!buf_dup(prev + fd, &cur, cur.pos + 1));
	}
	return (!!ret);
}
