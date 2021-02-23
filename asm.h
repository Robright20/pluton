/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <zael-mab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:48:45 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/03 14:22:25 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// fix the ft_printf macros !
#ifndef ASM_H
#define ASM_H

#include "libft/libft.h"
#include "op.h"
#include<fcntl.h> 
#include<errno.h>

typedef enum {F , T}    boolean;

typedef struct      s_node
{
    char            *data;
    size_t          position;
    int             operation_num;          //labels -pointes operation-
    int             op_code;
    int             op_arg1;
    int             op_arg2;
    int             op_arg3;
    char            *op_args[3];
    struct s_node   *next;
}                   t_node;

typedef struct      s_head
{
    size_t          l_size;
    struct s_node   *first;
}                   t_head;


typedef struct 	s_op 
{
	char 		name[5];
	int 		args_numb;
	int			args[3];
	int 		op_code;
	int			wait_to_run;
	char		des[60];
	int			x;
	int			dir_size;
}				t_op;


typedef struct      s_asmdata
{
    char            *name;
    char            *comment;
    int             n;
    int             c;
    int             s;
    int             e;
    int             error;
    int             p_ex_code;
}                   t_asmdata;

t_op            op_tab[17];




t_node      *insert_node(t_head *head, void    *data, int pos);
void        display_nodes(t_head *head);       //
void        init_head(t_head *head);
char 	    *avoid_comment (char *line);
boolean     check_champion (char *line, t_asmdata *sdata);
boolean     join (char *line, t_asmdata *sdata, char **cmd, int v);
t_node      *search(t_node *l, char* x);


t_node      *save_labels(t_head *labels, char *lin, t_head *head);
// void        creat_op_table(t_hop *op, int i);

void        pars_instructions(t_head *head, t_head *labels, t_asmdata *sdata);

void        operations(char **operat, int i);

int         pars_args(char  *instruction, t_asmdata *sdata, int y);


# endif
