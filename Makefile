
NAME = corewar
SRC = $(addprefix src/, read_players.c op.c verify_champ.c arena.c\
		processes.c battle.c tools.c convert.c tools1.c\
		opcode/add.c opcode/and.c opcode/fork.c opcode/live.c opcode/lld.c\
		opcode/lldi.c opcode/or.c opcode/st.c opcode/sti.c opcode/sub.c\
		opcode/xor.c opcode/zjmp.c opcode/ldi.c opcode/ld.c opcode/lfork.c)

HEADER = $(addprefix include/, vm.h op.h)
OBJ = $(SRC:.c=.o)
LFTDIR = ./libft
LDLIBS = -lft
LDFLAGS = -L$(LFTDIR)
CFLAGS = -Wall -Wextra -Werror -g  -I./include
CC = gcc
RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[93m
RESET		= \033[0m

all : $(LFTDIR) $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)
	@echo "⇾ building $(GREEN)corewar$(RESET)"

$(LFTDIR):
	@make -C $@

clean: 
	@$(RM) $(OBJ)
	@make -C $(LFTDIR) clean
	@echo "⇾ $(NAME) $(RED)cleaned$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LFTDIR) fclean
	@echo "⇾ $(NAME) $(RED)deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re $(LFTDIR)
