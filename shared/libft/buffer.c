/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bob <bob@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:09:43 by bob               #+#    #+#             */
/*   Updated: 2021/01/17 11:01:29 by bob              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

int		reset_buffer(t_buffer *buf)
{
	if (buf)
	{
		free(buf->ptr);
		buf->ptr = NULL;
		buf->size = 0;
		buf->pos = 0;
	}
	return (0);
}

int		del_buffer(t_buffer **buf)
{
	if (buf)
	{
		if (*buf)
		{
			free((*buf)->ptr);
			(*buf)->ptr = NULL;
		}
		free(*buf);
		buf = NULL;
	}
	return (0);
}

void	*buf_realloc(t_buffer *buf, size_t new_size)
{
	void	*tmp;

	tmp = buf->ptr;
	if (!(buf->ptr = ft_memalloc(new_size)))
		return (NULL);
	if (buf->size >= 0)
	{
		ft_memcpy(buf->ptr, tmp, buf->size);
		free(tmp);
	}
	return (buf->ptr);
}

int		buf_dup(t_buffer *dst, t_buffer *src, size_t begin)
{
	ssize_t	size;

	size = src->size - begin;
	if (size < 0 && !(size = 0))
		ft_memdel(&dst->ptr);
	else
		dst->ptr = ft_memdup(src->ptr + begin, size);
	dst->size = size;
	dst->pos = 0;
	return (0);
}

int		buf_set(t_buffer *buf, void *str, size_t size, ssize_t pos)
{
	buf->ptr = str;
	buf->size = size;
	buf->pos = pos;
	return (0);
}
