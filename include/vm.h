/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:56:22 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/03/20 13:41:43 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <sys/stat.h>
# include <fcntl.h>
# include "op.h"
# include <stdlib.h>
# include <stdio.h>
# include "viz.h"
# include "../ft_printf/libft/headers/libft.h"
# include "../ft_printf/headers/ft_printf.h"
# include "../ft_printf/headers/float_bigint.h"

typedef struct		s_op
{
	char			name[10];
	int				args_counter;
	char			args[3];
	int				opcode;
	int				cycle_to_wait;
	char			description[64];
	int				codage_byte;
	int				dir_size;
}					t_op;

extern	t_op		g_op_tab[];
int					g_unique_id;
int					g_viz_fd;

typedef struct		s_player
{
	char			*name;
	char			*comment;
	char			*code;
	int				size;
	int				id;
}					t_player;

typedef struct		s_players
{
	t_player		**player;
	int				*ids_av;
	int				verbos;
	int				dump;
	int				aff;
	int				number_of_players;
}					t_players;

typedef struct		s_game_para
{
	char			*arena;
	int				last_live;
	int				verbos;
	int				dump;
	int				aff;
	int				cycle_counter;
	int				cycle_to_die;
	int				check_counter;
	int				live_counter;
	int				last_live_counter;
	int				or_cycle_to_die;
	int				opcode_wait_cycles[17];
	t_players		*players;
}					t_game_para;

typedef struct		s_cursor
{
	int				pc;
	int				id;
	int				code_size;
	int				carry;
	int				opcode;
	int				args[3];
	int				last_live;
	int				wait_cycle;
	int				player_id;
	int				registeries[REG_NUMBER];
	struct s_cursor	*next;
}					t_cursor;

int					verify_champ(t_players *players, char *argv, int id);
void				delete_process(t_cursor *processes, int id);
int					init_arena(t_players *players, t_game_para *parameters,
																int *ids_av);
unsigned int		convert_to_numfd(int size, int fd);
t_cursor			*init_processes(t_players *players, int *ids_av);
t_cursor			*add_process(t_cursor *processes, t_players *players,
																	int id);
void				delete_process(t_cursor *processes, int id);
void				players_introduction(t_players *players, int *ids_av);
int					start_battle(t_cursor *processes, t_players *players,
																int *ids_av);
int					convert_to_num(char *str, int size);
int					*check_codage_byte(int codage_byte, int op);
unsigned int		get_vfarena(char *arena, int n, int pc);
int					sti(t_cursor *processes, t_game_para *parameters,
																int *size);
int					and(t_cursor *processes, t_game_para *parameters,
																int *size);
int					or(t_cursor *processes, t_game_para *parameters, int *size);
int					xor(t_cursor *processes, t_game_para *parameters,
																int *size);
int					ld(t_cursor *processes, t_game_para *parameters, int *size);
int					live(t_cursor *processes, t_game_para *parameters);
int					st(t_cursor *processes, t_game_para *parameters, int *size);
int					add(t_cursor *processes, t_game_para *parameters);
int					sub(t_cursor *processes, t_game_para *parameters);
int					ldi(t_cursor *processes, t_game_para *parameters,
																	int *size);
int					lld(t_cursor *processes, t_game_para *parameters,
																	int *size);
int					zjmp(t_cursor *processes, t_game_para *parameters);
int					lldi(t_cursor *processes, t_game_para *parameters,
																	int *size);
int					ft_fork(t_cursor *processes, t_game_para *parameters,
														t_cursor **fprocesses);
int					lfork(t_cursor *processes, t_game_para *parameters,
														t_cursor **fprocesses);
t_cursor			*fork_child(t_cursor *processes, t_cursor **fprocesses);
t_game_para			*init_game_parameters(t_players *players, int *ids_av);
int					get_args(t_cursor *processes, t_game_para *parameters,
															int *size);
t_cursor			*remove_process(t_cursor *process, t_cursor *processes,
													t_game_para *parameters);
void				cpy_toarena(int reg, t_game_para **parameters, int index,
																		int n);
int					if_arg_tind(t_cursor *processes, t_game_para *parameters,
																		int i);
int					dump_arena(t_game_para *parameters);
int					print_usage(void);
void				free_resources(t_players *players, int *ids_av);
void				check_processes(t_cursor **processes,
													t_game_para *parameters);
#endif
