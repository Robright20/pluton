/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <zael-mab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:48:24 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/03 14:22:42 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// name;
// Comment;
// Executable code;
//

//              FOR PARS:
// in one line - one instruction. "sequence of instructions"
//      Empty lines, comments, as well as extra tabs or spaces are ignored.

// verything between the character '#' and the end of the line is considered a comment. 

// An empty string is a valid champion name : [ .name "" ]
//      but But lack of the string is an error: [ .name  ] (same case for the comment)

// Also, in the file .s must be present champion's comment.

// the command  " .extend " -and all other commands excepting '.name' and '.comment'- detected as an error


//                  FOR EXUECUTABLE CODE:
//  Assembly language has a rule one instruction per line. The new line character \n means both end
//       of line and end of instruction. So instead of ; as for C language, we will use \n.

//      Each redcode instruction contains 3 parts : Opcode itself, the source address A-field 
//          and the destination address B-field.





boolean     check_champion (char *line, t_asmdata *sdata)
{
    int j;

    if (ft_strscmp(NAME_CMD_STRING, line, 0, 5) == 0)
        sdata->n = 1;
    if (ft_strscmp(COMMENT_CMD_STRING, line, 0, 8) == 0)
        sdata->c = 1;

    if (ft_strscmp(NAME_CMD_STRING, line, 0, 5) == 0 || ft_strscmp(COMMENT_CMD_STRING, line, 0, 8) == 0)
    {
        sdata->error = -1;
        sdata->e = 0;
        sdata->s = 0;
    }

/////////////////////
    j = -1;
    while (line[++j])
    {
        if (line[j] == '"' && sdata->s && !sdata->e)
            sdata->e = j + 1;
        if (line[j] == '"' && !sdata->s)
            sdata->s = j + 1;
    }

/////////////////////
    if (sdata->n == 1 && sdata->s && sdata->e && sdata->error == -1)
        if ((sdata->name = ft_strscpy(ft_strnew(PROG_NAME_LENGTH), line, sdata->s, sdata->e)))
            sdata->n = -1;
 
    if (sdata->c == 1 && sdata->s && sdata->e && sdata->error == -1)
        if((sdata->comment = ft_strscpy(ft_strnew(COMMENT_LENGTH), line, sdata->s, sdata->e)))
            sdata->c = -1;

/////////////////////
    if (sdata->s && (sdata->c == 1 || sdata->n == 1))
    {

        sdata->error++;
        if (sdata->n == 1)
            join(line, sdata, &sdata->name, PROG_NAME_LENGTH);
        if (sdata->c == 1)
            join (line, sdata, &sdata->comment, COMMENT_LENGTH);
        return (1);
    }

    return (1);
}


boolean         join (char *line, t_asmdata *sdata, char **cmd, int v)
{
    char *tmp;

    tmp = ft_strnew(ft_strlen(line));
    if (sdata->error == 0)
        *cmd = ft_strjoin (ft_strnew(v), line + sdata->s);
    if (sdata->error > 0 && !sdata->e)
        *cmd = ft_strjoin (*cmd, line);
    if (sdata->error > 0 && sdata->e)
    {
        *cmd = ft_strjoin(*cmd, ft_strscpy(tmp, line, 0, sdata->e));
        sdata->c = (sdata->c == 1 ? -1 : sdata->c);
        sdata->n = (sdata->n == 1 ? -1 : sdata->n);
    }
    free (tmp);
    return (1);
}

//////////////////////////////////////////////////


void        pars_instructions(t_head *head, t_head *labels, t_asmdata *sdata)       //REG_NUMBER
{
    t_node  *instruct;
    t_node  *lbl;
    char *tmp;
    int i;

    instruct = NULL;
    lbl = NULL;
    instruct = head->first;
    sdata->p_ex_code = -1;

    while (instruct != NULL)
    {
        // ft_printf ("instructions.%d= %s\n", instruct->position, instruct->data);
        i = -1;
        while (instruct->data[++i])
            if (instruct->data[i] < 'a' || instruct->data[i] > 'z')
                break;
    /////////////////
        if (i > 0)
        {
            tmp = ft_strncpy(ft_strnew(5), instruct->data, i);
            int x = -1;
            while (++x < 17)
            {
                if (!ft_strcmp(tmp, op_tab[x].name) && pars_args(instruct->data + i, sdata, x))
                {
                    ft_printf ("mutch %s ==> [%s]\n", op_tab[x].name, tmp);
                    pars_args(instruct->data + i, sdata, x);
                    break ;
                }
            }
            ft_printf("%d", sdata->error);
            // ft_printf ("list[%s] ===>   tmp[%s]\n", op_list->name, instruct->data);
            free (tmp);
        }
    //////////////////////
        // while (op_list)
        // {
            // if ( i > 0 && !ft_strcmp(op_list->name, tmp))
            // {
                // ft_printf("[%d]_%s |\t %s \n", op_list->code, instruct->data, op_list->name);
                // pars_args(instruct->data + i, op_list);

                // instruct->op_code = op_list->code;
                // instruct->op_arg1 = op_list->arg1;
                // instruct->op_arg2 = op_list->arg2;
                // instruct->op_arg3 = op_list->arg3;
            // }

            lbl = labels->first;
            // while (lbl)          use the searsh(); !!!
                // lbl = lbl->next;        
        // }
            ////////
            instruct = instruct->next;
    }
}


