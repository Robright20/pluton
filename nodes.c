#include "lem_in.h"


t_node  *add_first(t_head *head, void* data)
{
    t_node *new_node;

    new_node = ft_memalloc (sizeof (t_node));
    new_node->data = data;
    new_node->next = head->first;
    head->first = new_node;
    head->size +=1;
    return (new_node);
}

t_node  *search(t_node *l, void* x)
{
    if (l == NULL)
        return NULL;
    if (l->data == x)
        return (l);
    else
        return (search(l->next, x));

}

t_node  *push_list (t_head *head, void * data)
{
    t_node *new_node;

    new_node = ft_memalloc (sizeof (t_node));
    new_node->data = ft_strdup(data);
    new_node->next = NULL;

    if (head->first == NULL)
    {
        head->size +=1;
        head->first = new_node;
    }
    else
    {
    //////////////////////////////////////
        t_node *p = head->first;
        int d = -1;

        if (ft_strcmp(head->first->data , data) > 0)
        {
            new_node->next = head->first;
            head->first = new_node;
        }
        else
        {
            while (p->next != NULL)
            {
                if (ft_strcmp(p->next->data , data) > 0)
                {
                    d = 0;
                    new_node->next = p->next;
                    p->next = new_node;
                    break ;
                }
                if (ft_strcmp(p->next->data, data) == 0)
                {
                    free (new_node);
                    return NULL;
                }
                p = p->next;
            }
        /////////////////////////////////////////
            if (d == -1)
                p->next = new_node;
        }
        head->size += 1;
    }
    return (new_node);
}

///////////////////////////

void    display (t_head *head)
{
    t_node *p;

    p = head->first;
    while (p != NULL)
    {
        ft_printf (" *[%s]P(%d) ", p->data, p->pos);
        p = p->next;
    }
    ft_printf ("\n");
}

/////////////////////

void    init_list_table (t_table **table, int size)
{
    int i;

    i =-1;
    while (++i < size)
        table[i]->head = ft_memalloc (sizeof (t_head));
}

boolean     insert_graph (t_head *head, void *x, int y)
{
    t_node *new_node;

    new_node = ft_memalloc (sizeof (t_node));
    new_node->data = ft_strdup(x);
    // ft_printf ("\t[data = %s] -- [data.x = %d]\n", x, data.y);
    new_node->pos = y;
    new_node->state = 0;
    new_node->next = NULL;
    if (head->first == NULL)
    {
        head->first = new_node;
        head->size += 1;
        return (1);
    }
    else
    {
    ///////////////////////////
        t_node *p;
        p = head->first;
        while (p->next != NULL)
        {
            if (ft_strcmp(x, p->data) == 0)
            {
                free (new_node);
                return (0);
            }
            p = p->next;
        }
        if (ft_strcmp (x, p->data) == 0)
        {
            free(new_node);
            return (0);
        }
        p->next = new_node;
        head->size += 1;
        return (1);
    }
    return (0);
}
/////////////////////

void    init_table(t_table **table, int size)
{
    int i;
    
    i = -1;
    while (++i < size)
        table[i] = NULL;
}


void    print_table (t_table **table, int size)
{
    int i;

    i = -1;
    while (++i < size)
    {
        if (table[i] == NULL)
            ft_printf ("\t%d\t-------\n", i);
        else
        {
            ft_printf ("\t%d==>[%s]", i, table[i]->data);
            display (table[i]->head);
        }
    }
}

boolean     insert_table (t_table **table, t_head *head, t_data0 data)
{
    t_table *p;
    t_node *pt;
    size_t l;

    pt = head->first;
    l = 0;
    while (l < data.table_size)
    {
        p = ft_memalloc (sizeof (t_table));
        if (pt->data == NULL)
            return 0;
        p->data = ft_strdup(pt->data);
        if (table[l] != NULL)
            return 0;
        table[l] = p;
        pt = pt->next;
        l++;
    }
    return 1;
}


////////////////////////////

void    *list_get (t_head *head)
{
    t_node  *tmp;
    void    *data;

    if (head->first == NULL)
        return (NULL);
    tmp = head->first;
    data = tmp->data;
    head->first = head->first->next;
    head->size--;
    free(tmp);
    return (data);
}

void    list_del_all (t_head *head)
{
    while (head->first != NULL)
        list_get(head);
}


//  try new sort & search methods ;
//  minimize the error parts and the loops for each line;
//  free ****;
//  norme