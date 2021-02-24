/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:44:27 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/21 17:44:35 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


int         check_reg(char *line, int arg);


int         pars_args(char  *instruction, t_asmdata *sdata, int y)
{
    int j;
    int x;
    int w;

    j = -1;
    w = y;
    x = 0;
    int cnt = -1;       //
    char **tab = ft_strsplit(instruction, ',');

    ft_printf ("-_-_-_-_-_-_-_-_-_-%s-_-_-_-_-_-\n", sdata->name);
    while (tab[++j])
    {
        x = -1;
        // cnt = op_tab[x].args[j];
        while (tab[j][++x])
        {
            
            if (tab[j][x] == 'r' && ft_isdigit(tab[j][x + 1]))
            {
                // if (ft_atoi(x + 1 + tab[j]) < 1 || ft_atoi(x + 1 + tab[j]) > 16)
                //     ft_printf ("Error! %d \n", ft_atoi(x + 1 + tab[j]));
                ft_putchar ('R');
                // check_reg(tab[j], cnt);
                break ;
            }
            if (tab[j][x] == 'r' && !ft_isdigit(tab[j][x + 1]))
                ft_printf("!Error\n");
            else if (tab[j][x] == '%')                          //DIRECT_CHAR (%) and a number or label (LABEL_CHAR (:) in front of it)
            {
                //check_dir();
                ft_putchar ('D');
                break ;
            }
            else if (ft_isdigit(tab[j][x]))
            {
                ft_putchar ('I');
                // check_ind();
                break ;
            }
        }
        ft_printf("-%s-\n", tab[j]);

    }
    return (1);
}

int         check_reg(char *line, int arg)
{
    char *tmp = ft_strtrim(line);
    int i;

    i = -1;
    while (tmp[++i])
    {
        if (tmp[i] == 'r' && ft_atoi( 1 + tmp) > 0 && ft_atoi( 1 + tmp) > 0)
        {
            if (!(arg & T_REG))
            {
                ft_printf ("arg number [%s] wrrong\n", tmp);
                break ;
            }
            else
            {
                ft_putstr ("(r) are good");
                break;
            }
        }
        else
        {
            ft_printf ("Error [%s] \n", tmp);
            break ;
        }
    }

    free(tmp);
    return (1);
}