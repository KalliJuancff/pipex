CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall

.PHONY : comp norm

comp :
	$(CC) $(CFLAGS) libft/ft_strlen.c libft/ft_split.c libft/ft_strlcpy.c libft/ft_strnstr.c libft/ft_strncmp.c libft/ft_strjoin.c libft/ft_strlcat.c pipex.c pipex_init.c pipex_err_mgmt.c pipex_exec_cmds.c pipex_redir_cmds.c -o pipex.out


norm :
	norminette *.c pipex.h

clean :
	rm -f pipex.out
