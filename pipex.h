/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:27:15 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/08 20:17:53 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

	// errno
# include <errno.h>
	// open, O_CREAT, OWR_ONLY, S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH
# include <fcntl.h>
	// perror
# include <stdio.h>
	// exit, wait
# include <stdlib.h>
	// STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, ...
	// ... close, dup2, fork, getpid, pid_t, pipe, read, write
# include <unistd.h>

# include "libft/libft.h"

# define ERR_NUM_PARAMS_KO -1

# define READ_END 0
# define WRITE_END 1

struct	s_prgdata
{
	char		*infile;
	char		*outfile;
	char		**commands;
	int			commands_number;
};
typedef struct s_prgdata	t_prgdata;

void	validate_arguments(int argc, char *argv[]);
void	initialize_program_data(t_prgdata *dt, int argc, char *argv[]);
void	release_program_data(t_prgdata dt);

void	redirect_first_command(t_prgdata dt, int pipefd[2]);
void	redirect_last_command(t_prgdata dt, int prev_read_fd);
void	redirect_middle_command(int prev_read_fd, int pipefd[2]);

void	ft_exit(void);
void	ft_exit2(int err_code, char *err_msg);

#endif
