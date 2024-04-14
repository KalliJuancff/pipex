NAME      := pipex
SRC_FILES := pipex.c \
	pipex_init.c \
	pipex_exec_cmds.c \
	pipex_redir_cmds.c \
	pipex_err_mgmt.c
SRC_FILES_BONUS := pipex_bonus.c \
	pipex_init_bonus.c \
	pipex_exec_cmds_bonus.c \
	pipex_redir_cmds_bonus.c \
	pipex_err_mgmt_bonus.c
		# Utilizando 'substitution reference'
OBJ_FILES := $(SRC_FILES:.c=.o)
OBJ_FILES_BONUS := $(SRC_FILES_BONUS:.c=.o)
		# Utilizando la funcion 'patsubst'
DEP_FILES := $(patsubst %.c,%.d,$(SRC_FILES))
DEP_FILES_BONUS := $(patsubst %.c,%.d,$(SRC_FILES_BONUS))
CFLAGS := -Wall -Wextra -Werror -MMD
LIBFT_DIR := libft
LIBFT_FILENAME := libft.a

$(NAME) : $(LIBFT_DIR)/$(LIBFT_FILENAME) $(OBJ_FILES)
	$(CC) $(LIBFT_DIR)/$(LIBFT_FILENAME) $(OBJ_FILES) -o $(NAME)

-include $(DEP_FILES)

$(LIBFT_DIR)/$(LIBFT_FILENAME) :
	$(MAKE_COMMAND) -C $(LIBFT_DIR)

%.o : %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all clean fclean re norm debug

all : $(NAME)

clean :
	$(RM) $(OBJ_FILES)
	$(RM) $(DEP_FILES)
	$(MAKE_COMMAND) -C $(LIBFT_DIR) clean

fclean : clean
	$(RM) $(NAME)

re : fclean all

norm :
	@norminette $(SRC_FILES) $(NAME).h

debug :
	$(info SRC FILES (MANDATORY) : $(SRC_FILES))
	$(info SRC FILES (BONUS)     : $(SRC_FILES_BONUS))
	$(info OBJ FILES (MANDATORY) : $(OBJ_FILES))
	$(info OBJ FILES (BONUS)     : $(OBJ_FILES_BONUS))
	$(info DEP FILES (MANDATORY) : $(DEP_FILES))
	$(info DEP FILES (BONUS)     : $(DEP_FILES_BONUS))

