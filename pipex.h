/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:27:15 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/07 15:40:21 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

# define ERR_NUM_PARAMS_KO 1
# define ERR_EXECUTING_MALLOC 2
# define ERR_EXECUTING_FORK 3

struct	s_prgdata
{
	char		*infile;
	char		*outfile;
	char		**commands;
	int			commands_number;
};
typedef struct s_prgdata	t_prgdata;

void	validate_arguments(int argc, char *argv[]);
void	initialize_program_data(t_prgdata *data, int argc, char *argv[]);
void	release_program_data(t_prgdata data);

void	ft_exit(int errcode);
void	ft_exit2(int errcode, char *errdesc);

#endif
