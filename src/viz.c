/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bob <bob@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 10:31:06 by fokrober          #+#    #+#             */
/*   Updated: 2021/02/05 08:54:38 by fokrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "viz.h"
#include "libft.h"
#define TIMEOUT 30
#define SLEEP 5

/*
** returns a 0 if success and non-null if error
** don't forget to use v_await() to wait for the
** child process and close the other side of the
** pipe.
** 
** fd[0] => read from the subprocess
** fd[1] => write from the subprocess
** 
** opt = 'r' => read from the subprocess
** opt = 'w'/others => write from the subprocess
*/

int		v_spawn(int *fd, int opt)
{
	pid_t	child;
	int		child_fd;
	int		ret;

	if (pipe(fd) < 0)
		return (1);
	child_fd = opt == 'r' ? 1 : 0;
	child = fork();
	if (child < 0)
		ret = write(2, "error\n", 6);
	else if (child > 0)
		ret = close(fd[child_fd]);
	else
	{
		close(fd[!child_fd]);
		dup2(fd[child_fd], child_fd);
		if ((ret = execl(RUN_SRV, "", (void*)NULL)) < 0)
			ft_putendl_fd("[exec launcher] FAIL !\n", child_fd);
	}
	return (ret);
}

int		v_socket_connect(void)
{
	t_sckaddr	serv_addr;
	int			sock;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		ft_putendl_fd("socket creation failed", 2);
		return (-1);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	if (inet_pton(AF_INET, SERV_ADDR, &serv_addr.sin_addr) <= 0)
	{
		ft_putendl_fd("[v_socket_connect]: Invalid address", 2);
		return (-1);
	}
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))
	{
		perror("[v_socket_connect]");
		return (-1);
	}
	return (sock);
}

int		v_init(void)
{
	int		ret;
	char	*line;
	int		await_time;

	ret = v_socket_connect();
	await_time = 0;
	while (ret > 0 && await_time < TIMEOUT)
	{
		write(ret, "##check-client\n", 15);
		if (get_next_line(ret, &line) > 0 && ft_strnequ("ACK", line, 3))
		{
			ft_strdel(&line);
			break ;
		}
		ft_putendl_fd(line, 1);
		ft_strdel(&line);
		sleep(SLEEP);
		await_time += SLEEP;
	}
	(void)(await_time >= TIMEOUT && write(1, "NO_HTTP_CLIENT: timeout\n", 24));
	return (ret > 0 && await_time < TIMEOUT ? ret : -1);
}

void	v_await(int *fd, int child_fd)
{
	wait(NULL);
	close(fd[child_fd]);
}

void	v_ack_await(int fd)
{
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{
		ft_putendl_fd(line, 1);
		if (ft_strnequ("ACK", line, 3))
			break ;
		ft_strdel(&line);
	}
	ft_strdel(&line);
}
