/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:27:15 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/12 18:16:34 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

	// errno
# include <errno.h>
	// open, ...
	// ... O_CREAT, OWR_ONLY, O_TRUNC, S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH, ...
	// ... O_RDONLY
# include <fcntl.h>
	// perror
# include <stdio.h>
	// exit, wait
# include <stdlib.h>
	// STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, ...
	// ... close, dup2, fork, getpid, pid_t, pipe, read, write
# include <unistd.h>

# include "libft/libft.h"

# define ERR_INVALID_NUM_PARAMS -1
# define ERR_PATH_ENV_VAR_NOT_FOUND -2
# define ERR_FILE_NOT_FOUND -3

# define READ_END 0
# define WRITE_END 1

struct	s_prgdata
{
	char	*infile;
	char	*outfile;
	int		commands_number;
	char	**commands;
	char	**env_variables;
	char	**path_dirs;
};
typedef struct s_prgdata	t_prgdata;

void	validate_arguments(int argc, char *argv[]);
void	init_program_data(t_prgdata *dt, int argc, char *argv[], char *envp[]);
void	release_program_data(t_prgdata dt);

void	execute_command(t_prgdata dt, int ndx);
void	execute_first_command(t_prgdata dt, int ndx, int *prev_fd);
void	execute_last_command(t_prgdata dt, int ndx, int prev_fd, int *last_pid);
void	execute_middle_command(t_prgdata dt, int ndx, int *prev_fd);
int		execute_pipeline(t_prgdata dt);

void	redirect_first_command(t_prgdata dt, int pipefd[2]);
void	redirect_last_command(t_prgdata dt, int prev_read_fd);
void	redirect_middle_command(int prev_read_fd, int pipefd[2]);

void	exit_with_internal_error(void);
void	exit_with_custom_error(int err_code, char *err_msg);

char	*get_value_of_environment_variable(char *envp[], char *var_name);
char	**get_path_directories(char *path_value);
char	*expand_filename(char **path_dirs, char *filename);

#endif
