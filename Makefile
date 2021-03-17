NAME 		= corewar
SRC 		= $(addprefix src/, read_players.c op.c verify_champ.c arena.c\
				processes.c battle.c tools.c convert.c tools1.c\
				opcode/add.c opcode/and.c opcode/fork.c opcode/live.c opcode/lld.c\
				opcode/lldi.c opcode/or.c opcode/st.c opcode/sti.c opcode/sub.c\
				opcode/xor.c opcode/zjmp.c opcode/ldi.c opcode/ld.c opcode/lfork.c)

HEADER 		= $(addprefix include/, vm.h op.h)
FT_PRINTF 	= ft_printf
LIBPRINTF 	= ft_printf/libftprintf.a
CFLAGS 		= -Wall -Wextra -Werror -I./include
CC 			= gcc
OBJ 		= $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) $(HEADER) $(LIBPRINTF)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBPRINTF)
	@echo "\033[1;34m>>\033[0m corewar: \033[1;32m corewar compilled.\033[0m"

$(LIBPRINTF): force
	@make -C $(FT_PRINTF)

force:

clean: 
	@$(RM) $(OBJ)
	@make clean -C $(FT_PRINTF)
	@echo "\033[1;34m>>\033[0m $(NAME): \033[1;33m object files deleted.\033[0m"

fclean:
	@$(RM) $(NAME)
	@make fclean -C $(FT_PRINTF)
	@echo "\033[0;34m>>\033[0m $(NAME): \033[0;31m deleted.\033[0m"

re: fclean all

.PHONY: all clean fclean re force
