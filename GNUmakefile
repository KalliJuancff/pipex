CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall

.PHONY : comp comp_mandatory comp_bonus norm

comp : comp_mandatory comp_bonus

comp_mandatory :
	$(CC) $(CFLAGS) libft/ft_strlen.c libft/ft_split.c libft/ft_strlcpy.c libft/ft_strnstr.c libft/ft_strncmp.c libft/ft_strjoin.c libft/ft_strlcat.c pipex.c pipex_init.c pipex_err_mgmt.c pipex_exec_cmds.c pipex_redir_cmds.c -o pipex.out

comp_bonus :
	$(CC) $(CFLAGS) libft/ft_strlen.c libft/ft_split.c libft/ft_strlcpy.c libft/ft_strnstr.c libft/ft_strncmp.c libft/ft_strjoin.c libft/ft_strlcat.c pipex_bonus.c pipex_init_bonus.c pipex_err_mgmt_bonus.c pipex_exec_cmds_bonus.c pipex_redir_cmds_bonus.c -o pipex_bonus.out

norm :
	norminette *.c pipex.h pipex_bonus.h

clean :
	rm -f pipex.out
	rm -f pipex_bonus.out
