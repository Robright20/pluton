/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 10:30:26 by fokrober          #+#    #+#             */
/*   Updated: 2021/03/20 13:41:42 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIZ_H
# define VIZ_H
# define V_NODE "##visiting-node"
# define V_EDGE "##visiting-edge"
# define V_NODE_OK "##visited-node"
# define V_EDGE_OK "##visited-edge"
# define SERV_ADDR "127.0.0.1"
# define SERV_PORT 8000
# define RUN_SRV "./viz/run_server.sh"
# include <arpa/inet.h>
# include <netinet/in.h>

typedef struct sockaddr_in	t_sckaddr;

void	v_await(int *fd, int child_fd);
int		v_init(void);
int		v_spawn(int *fd, int opt);
void	v_ack_await(int fd);
#endif
