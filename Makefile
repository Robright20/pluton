# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zael-mab <zael-mab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 05:40:09 by zael-mab          #+#    #+#              #
#    Updated: 2021/02/03 14:17:43 by zael-mab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRC = 	main.c\
		link_lst.c\
		op.c\
		pars_name_com.c\
		check_args.c\
		args.c\
		convert.c\
		pars_instr.c\
		pars_args_lbl.c\
		set_data.c\
		m_error.c\
		set_nc_encodin.c\
		clean.c
OBJ = $(SRC:.c=.o)

HEADER = asm.h
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror 
LDFLAGS = -L$(LIBFT_DIR)
LDLIBS = -lft

# =========================================================================== #

all: depbuild $(NAME)

depbuild:
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(HEADER) 
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME)


clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "done\033[0m"

re: fclean all
