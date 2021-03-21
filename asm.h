/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:57:27 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 15:06:42 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft/libft.h"
# include "op.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

typedef struct		s_node
{
	char			*data;
	size_t			position;
	size_t			code;
	int				arg_num;
	int				encodin_code;
	int				encodin;
	int				op_code;
	int				w_args[9];
	int				lb;
	int				arg[3];
	char			**arg_tab;
	size_t			command_size;
	struct s_node	*next;
}					t_node;

typedef struct		s_head
{
	size_t			l_size;
	size_t			code_size;
	struct s_node	*first;
}					t_head;

typedef struct		s_label
{
	char			*data;
	size_t			operation_num;
	size_t			position;
	int				size_ind;
	struct s_label	*next;
}					t_label;

typedef struct		s_head_lb
{
	size_t			l_size;
	size_t			code_size;
	struct s_label	*first;
}					t_head_lb;

typedef struct		s_op
{
	char			name[5];
	int				args_numb;
	int				args[3];
	int				op_code;
	int				wait_to_run;
	char			des[60];
	int				encoding_code;
	int				dir_size;
}					t_op;

typedef struct		s_asmdata
{
	char			*name;
	char			*comment;
	char			*file_name;
	char			*line;
	int				ln;
	int				n;
	int				c;
	int				s;
	int				e;
	int				error;
	char			**op_tb;
	int				x;
	int				y;
	int				z;
}					t_asmdata;

t_op				g_op_tab[17];

int					check_extention(char *line, t_asmdata *data);
void				f_assembler (t_head *head, t_asmdata *data, int fd);
int					read_set_data(t_asmdata *data, t_head *head,
		t_head_lb *labels);
void				clean_data(t_asmdata *data, t_head_lb *labels,
		t_head *head);
int					check_champion_name_comment(t_asmdata *data);
int					cmp_nm_cm(char *line);
char				*avoid_comment (char *line);
int					save_labels_and_commands(t_head_lb *labels, char *line,
		t_head *head, t_asmdata *data);
int					search_forlbl_char(char *line, char **tmp);
int					check_champion (char *line, t_asmdata *data);
int					set_jumper(t_asmdata *data, char *line, int j);
int					search_for_exention(char *line, t_asmdata *data, int j);
int					pars_chmp_nm_cm(t_asmdata *sdata, char *line);
int					join (char *line, t_asmdata *sdata, char **cmd, int v);
void				join_last_line(t_asmdata *data, char **cmd, char *line);
void				assembly_to_bytecode(t_head *head, t_asmdata *data,
		t_head_lb *labels);
int					pars_instructions(t_head *head, t_head_lb labels,
		t_asmdata *sdata);
int					set_label_args(t_head *head, t_head_lb labels,
		t_asmdata *data);
int					get_labels_value(t_label *l, t_node *instru,
		t_label *first, int counter);
int					check_digit(char *line);
int					reverse_endian (int i);
void				to_byte_code(t_head *head, t_asmdata *data);
void				decode(t_asmdata *data, t_head *cmmnd, int fd);
void				writ_args(t_asmdata *data, t_node *cmd, int fd);
void				search_for_labels_init(t_head_lb labels,
		t_node *instr, t_head *head);
void				init_oper_data(t_node *instr, t_asmdata *data, int x);
int					check_oper(t_node *instr, t_head_lb labels,
		t_head *head, t_asmdata *data);
int					pars_args(t_node *instruction, t_asmdata *data,
		int y, t_head_lb labels);
int					count_separator_char(char *line, t_asmdata *data);
int					trt_cmd(t_asmdata *data, t_node *instruct,
		t_head_lb labels, t_head *head);
int					trt_arg(t_asmdata *data, t_node *instr,
		t_head_lb labels, int y);
void				add_encodin_code(t_asmdata *sdata, t_node *instruct);
void				init_encodin_byte(t_node *instr, int p, int shift);
int					reg_lexical_analysis (t_asmdata *data,
		t_node *instr, int y);
int					dirl_lexical_analysis (t_asmdata *data, t_node *instr,
		t_head_lb labels, int y);
int					dir_lexical_analysis (t_asmdata *data,
		t_node *instr, int y);
int					ind_lexical_analysis (t_asmdata *data, t_node *instr,
		t_head_lb labels, int y);
int					ind_lb(t_asmdata *data, t_head_lb labels,
		t_node *instr, int y);
int					check_reg(char *line, int arg, t_node *instru,
		t_asmdata data);
int					check_dir_lebel(char *line, int arg, t_head_lb labels);
int					check_dir(char *line, int arg, t_node *instr,
		t_asmdata data);
int					check_ind(char *line, int arg, t_head_lb labels);
int					check_isdigit(char *tmp, int j);
t_label				*insert_label(t_head_lb *head, void *data, int pos);
t_node				*insert_node(t_head *head, void *data);
t_label				*search_by_pos(t_label *l, size_t x);
t_label				*search_by_name(t_label *l, char *x);
int					print_oper_error(char *line, t_asmdata *data);
int					print_arg_error(t_node instr, t_asmdata *data,
		int j, int lb);
void				check_error(t_asmdata *data, t_head_lb labels,
		t_head *head);
void				*list_get(t_head *head);
void				list_del_all (t_head *head);
void				*list_get_lb(t_head_lb *head);
void				list_del_all_lb (t_head_lb *head);

#endif
