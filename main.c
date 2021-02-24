/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <zael-mab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:48:04 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/03 14:22:00 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// repeat.
// read the next Assembly command
// break it into the different fields it is composed of .
// lookup the binary code for each field.
// combine these code into a single machine language command.
// output this machine language command.


int main(int ac, char **av)
{
	if (ac == 2)
	{
		char 		*line;
		int 		fd;
		int 		ln;
		// char 		*tmp;
		t_head 		head;
		// t_hop 		op;
		t_head		labels;
		t_asmdata	sdata;

		ft_bzero (&head, sizeof (t_head)); 
		// ft_bzero (&op, sizeof (t_hop)); 
		ft_bzero (&labels, sizeof (t_head));
		ft_bzero (&sdata, sizeof (t_asmdata));
		init_head (&head);
		init_head (&labels);
		// init_op(&op);

// /////////////////////////////////////
		fd = open(av[1], O_RDONLY);
		sdata.error = -1;

		// set_op_table(&op);
		
		ln = 0;
		while (get_next_line(fd, &line) > 0)
		{
			// tmp = ft_strtrim(line);
			// free (line);
			// line = tmp;

			if (sdata.n == -1 && sdata.c == -1)
				line = avoid_comment(line);							// avoid comment 
			
			// ft_printf("-------%s\n", line);

			if (sdata.n == -1 && sdata.c == -1)		//	avoid empty lines
					save_labels(&labels, ft_strtrim(line), &head);

			check_champion(line, &sdata);								// check and save the name & the comment

			free (line);
			ln++;									// I'll need ya later.
		}

///////////////***********///////////
		ft_printf ("\t[%s] | [%s]\t %d\n", sdata.name, sdata.comment, sdata.p_ex_code);
		ft_printf ("\t----------\n");
		// display_nodes (&labels);
		ft_printf ("\t----------\n");
		// display_nodes (&head);
		ft_printf ("\t-----*----\n\n");
/////////////***********///////////

		pars_instructions(&head, &labels, &sdata);

		close (fd);
	}
	
	if (ac == 1)
		ft_printf ("No file detected!\n");
	if (ac > 2)
		ft_printf ("Too many files!\n");
}


char 	*avoid_comment (char *line)				// deal with the comments  !!!
{
	int i;
	char *str;

	i = -1;
	while (line[++i])
	{
		if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT_CHAR)
		{
			str = ft_strncpy(ft_strnew (i), line, i);
			free (line);
			return (str);
		}
	}
	return (line);
}
