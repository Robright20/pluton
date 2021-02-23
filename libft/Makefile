# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/29 22:23:38 by zael-mab          #+#    #+#              #
#    Updated: 2020/03/02 23:38:32 by zael-mab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC_PATH= .
SRC_NAME=popac.c\
		 stdarg0.c\
		 ft_strscpy.c\
		 bo.c\
		 dioux0.c\
		 dioux1.c\
		 lolot.c\
		 ft_strnnn.c\
		 opert.c\
		 opert2.c\
		 f_loat0.c\
		 f_loat1.c\
		 dioux1.c\
		 dioux1p.c\
		 xxp.c\
		 xxp0.c\
		 ft_atoi.c\
		 ft_itoa_u.c\
		 ft_bzero.c\
		 ft_isalnum.c\
		 ft_isalpha.c\
		 ft_isascii.c\
		 ft_isdigit.c\
		 ft_isprint.c\
		 ft_itoa.c\
		 ft_memalloc.c\
		 ft_memccpy.c\
		 ft_memchr.c\
		 ft_memcmp.c\
		 ft_memcpy.c\
		 ft_memdel.c\
		 ft_memmove.c\
		 ft_memset.c\
		 ft_putchar.c\
		 ft_putchar_fd.c\
		 ft_putendl.c\
		 ft_putendl_fd.c\
		 ft_putnbr.c\
		 ft_putnbr_fd.c\
		 ft_putstr.c\
		 ft_putstr_fd.c\
		 ft_strcat.c\
		 ft_strchr.c\
		 ft_strclr.c\
		 ft_strcmp.c\
		 ft_strcpy.c\
		 ft_strdel.c\
		 ft_strdup.c\
		 ft_strequ.c\
		 ft_striter.c\
		 ft_striteri.c\
		 ft_strjoin.c\
		 ft_strlcat.c\
		 ft_strlen.c\
		 ft_strmap.c\
		 ft_strmapi.c\
		 ft_strncat.c\
		 ft_strncmp.c\
		 ft_strncpy.c\
		 ft_strnequ.c\
		 ft_strnjoin.c\
		 ft_strnew.c\
		 ft_strnstr.c\
		 ft_strrchr.c\
		 ft_strsplit.c\
		 ft_strstr.c\
		 ft_strsub.c\
		 ft_strtrim.c\
		 ft_tolower.c\
		 ft_toupper.c\
		 get_next_line.c
SRC=  $(addprefix $(SRC_PATH)/, $(SRC_NAME))


OBJ_PATH= obj
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ= $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))


CFLAGS=  -Wall -Wextra -Werror
CC= gcc
HDR_FLAGS= -I.


all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "libft: library compilled"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC)  $(CFLAGS) $(HDR_FLAGS) -o $@ -c $<


clean:
	@rm -fr $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "libft: object files deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "libft: library deleted"

re: fclean all
	
