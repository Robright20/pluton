#include "libft.h"
#include <stdio.h>
int main (void)
{
    int i;
    int tab[5] = {213213, -21, 0, 531, 100000};

    i = 0;
    while (i < 5)
    {
        ft_printf ("M%s\n", ft_itoa(tab[i]));
        printf    ("S%s\n", ft_itoa(tab[i++]));
    }

}