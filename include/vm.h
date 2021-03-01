/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:22:33 by aalhaoui          #+#    #+#             */
/*   Updated: 2021/02/28 18:10:38 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <sys/stat.h>
# include <fcntl.h>
# include "op.h"
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef	struct		s_cursor	t_cursor;
typedef	struct 		s_op 		t_op;
typedef	struct		s_player	t_player;
typedef	struct		s_players	t_players;
typedef	struct		s_game_para	t_game_para;
typedef	struct		s_cursor	t_cursor;

struct				s_op
{
	char			name[10];
	int				args_counter;
	char			args[3];
	int				opcode;
	int				cycle_to_wait;
	char			description[64];
	int				codage_byte;
	int				dir_size;
};

extern	t_op		op_tab[17];

struct				s_player
{
	char			*name;
	char			*comment;
	char			*code;
	int				size;
	int				id;
};

struct				s_players
{
	t_player		**player;
	int				*ids_av;
	int				number_of_players;
};

struct				s_game_para
{
	char			*arena;
	int				last_live;
	int				cycle_counter;
	int				cycle_to_die;
	int				check_counter;
	int				live_counter;
	int				last_live_counter;
	int     		opcode_wait_cycles[17];
};

struct				s_cursor
{
	int				pc;
	int				id;
	int				code_size;
	int				carry;
	int				opcode;
	int				args[3];
	int				last_live;
	int				wait_cycle;
	char			*code;
	int				player_id;
	int				registeries[REG_NUMBER];
	t_cursor		*next;
};

int					verify_champ(t_players *players, char *argv, int id);
void				delete_process(t_cursor *processes, int id);
int					init_arena(t_players *players, t_game_para *parameters);
unsigned int		convert_to_numfd(int size, int fd);
t_cursor			*init_processes(t_players *players);
t_cursor			*add_process(t_cursor *processes, t_players *players, int id);
void				delete_process(t_cursor *processes, int id);
void				players_introduction(t_players *players);
int     			start_battle(t_cursor *processes, t_players *players);
int					convert_to_num(char *str, int size);
int					*check_codage_byte(int codage_byte, int op);
int					get_vfarena(t_cursor *processes, char *arena, int n, int pc);
int					sti(t_cursor *processes, t_game_para *parameters);
int					and(t_cursor *processes, int *size);
int					or(t_cursor *processes, int *size);
int					xor(t_cursor *processes, int *size);
int					ld(t_cursor *processes);
int					live(t_cursor *processes, t_game_para *parameters);
int					st(t_cursor *processes, t_game_para *parameters, int *size);
int					add(t_cursor *processes);
int					sub(t_cursor *processes);
int					ldi(t_cursor *processes, t_game_para *parameters);
int					lld(t_cursor *processes);
int					zjmp(t_cursor *processes);
int					lldi(t_cursor *processes, t_game_para *parameters);
int					ft_fork(t_cursor *processes, t_game_para *parameters,
															t_cursor *fprocesses);
int					lfork(t_cursor *processes, t_game_para *parameters,
															t_cursor *fprocesses);
t_cursor			*fork_child(t_cursor *processes, t_cursor *fprocesses);
t_game_para			*init_game_parameters(t_players *players);
void				execute_operations(t_cursor *processes, t_game_para *parameters,
														t_cursor *fprocesses);
int					get_args(t_cursor *processes, t_game_para *parameters, int *size);													
int					remove_process(t_cursor *process, t_cursor *processes);
int					remove_all_processes(t_cursor *processes, t_game_para *parameters);
void			cpy_toarena(int reg, t_game_para *parameters, int index, int n);
#endif
