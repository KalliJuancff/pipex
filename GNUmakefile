CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall

.PHONY : comp norm

comp :
	$(CC) $(CFLAGS) libft/ft_strlen.c libft/ft_split.c libft/ft_strlcpy.c libft/ft_strnstr.c libft/ft_strncmp.c libft/ft_strjoin.c libft/ft_strlcat.c pipex.c pipex_initialization.c pipex_error_management.c pipex_execution_commands.c pipex_redirection_commands.c pipex_misc.c -o pipex.out


norm :
	norminette *.c pipex.h

clean :
	rm -f pipex.out
