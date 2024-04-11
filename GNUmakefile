CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall

.PHONY : comp norm

comp :
	 $(CC) $(CFLAGS) libft/ft_strlen.c libft/ft_split.c libft/ft_strlcpy.c libft/ft_strnstr.c libft/ft_strncmp.c pipex.c pipex_initialize.c pipex_error_management.c pipex_redirection_commands.c -o pipex.out


norm :
	norminette *.c pipex.h

clean :
	rm -f pipex.out
