/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <zael-mab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:32:58 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/02 18:25:05 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "asm.h"

void    init_head(t_head *head)
{
    head = ft_memalloc (sizeof (t_head));
    head->first = NULL;
    head->l_size = 0;
}
///////////////////////////////////


t_node     *insert_node(t_head *head, void    *data, int pos)
{
    t_node  *new_node;
    t_node  *p;

    new_node = ft_memalloc (sizeof (t_node));
    new_node->data = data;
    new_node->operation_num = pos > -1 ? pos : -1;
    new_node->next = NULL;
    if (head->first == NULL)
    {
        head->first = new_node;
        new_node->position = head->l_size++;
    }
    else
    {
        p = head->first;
        while (p->next != NULL)
            p = p->next;
        p->next = new_node;
        new_node->position = head->l_size++;
    }
    return (new_node->position + 1 == head->l_size ? new_node : NULL);
}


t_node  *search(t_node *l, char* x)
{
    if (l == NULL)
        return NULL;
    if (!ft_strcmp(l->data, x))
        return (l);
    else
        return (search(l->next, x));

}


void        display_nodes(t_head *head)
{
    t_node *l;

    l = head->first;
    while (l)
    {
        ft_printf("_|%d|\t[%s]\t",  l->position, l->data);
        if (l->operation_num > -1)
            ft_printf ("-%d-", l->operation_num);
        ft_putchar ('\n');
        l = l->next;
    }
}



t_node    *save_labels(t_head *labels, char *line, t_head *head)
{
    int j;
    int i;
    char *tmp;
    static int tmp_post;
    t_node p;                       //[  marker: 
    t_node t;                       //  # End of file  ]   if a label didn't followed by '\n' at the end of file it's an error fix it .

    ft_bzero(&p, sizeof (t_node));
    ft_bzero(&t, sizeof (t_node));
    j = -1;
    while (line[++j])
        if (line[j] == LABEL_CHAR)
            break ;

///////////////////////
    if (ft_strlen(line) > j)
    {
        tmp = ft_strncpy(ft_strnew(j), line, j);
        i = -1;
        while (++i <= j)
            if (ft_isdigit(tmp[i]) ||  tmp[i] == 95 || (tmp[i] >= 97 && tmp[i] <= 122));
            else
                break ;

/////////////////
        ft_printf ("*****%c***\n", line[i]);
        if (j == i)
        {
            if (ft_strlen(line) > j + 1)
            {
                p = *insert_node (head, ft_strtrim (j + 1 +line), -1);					//	insert eash line 
                t = *insert_node(labels, tmp, p.position);
            }
            else
                t = *insert_node(labels, tmp, tmp_post);
            return (NULL);
        }
        free (tmp);
    }
    p = *insert_node (head, line, -1); 
    tmp_post = p.position + 1;	 
    return (NULL);
}

//////////////////////////////////