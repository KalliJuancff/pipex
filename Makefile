NAME      := pipex
SRC_FILES := pipex.c \
	pipex_init.c \
	pipex_exec_cmds.c \
	pipex_redir_cmds.c \
	pipex_err_mgmt.c
# Utilizando 'substitution reference'
OBJ_FILES := $(SRC_FILES:.c=.o)
# Utilizando la funcion 'patsubst'
DEP_FILES := $(patsubst %.c,%.d,$(SRC_FILES))
CFLAGS = -Wall -Wextra -Werror -MMD

$(NAME) : $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(NAME)

-include $(DEP_FILES)

.PHONY : all clean fclean re norm debug

all : $(NAME)

clean :
	$(RM) $(OBJ_FILES)
	$(RM) $(DEP_FILES)

fclean : clean
	$(RM) $(NAME)

re : fclean all

norm :
	@norminette $(SRC_FILES) $(NAME).h

debug :
	$(info SRC FILES: $(SRC_FILES))
	$(info OBJ FILES: $(OBJ_FILES))
	$(info DEP FILES: $(DEP_FILES))
