/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/07 15:44:06 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define READ_END 0
#define WRITE_END 1

void	show_program_data(t_prgdata data)
{
	int	i;

	printf(" Infile: %s\n", data.infile);
	i = 0;
	while (data.commands[i] != NULL)
	{
		printf("Cmd. #%d / %d: %s\n", i + 1, data.commands_number, data.commands[i]);
		i++;
	}
	printf("Outfile: %s\n", data.outfile);
}

void	exec_pipex(t_prgdata data)
{
	int		fds_pipe[2];
	int		fd_file;
	int		pid;
	int		flags;
	mode_t	mode;
	int		status;

	pipe(fds_pipe);
	pid = fork();
	if (pid == -1)
	{
		perror("Error en la ejecución de 'fork'.\n");
		exit(ERR_EXECUTING_FORK);
	}
	if (pid == 0)
	{
		flags = O_RDONLY;
		fd_file = open(data.infile, flags);
		dup2(fd_file, STDIN_FILENO);
		close(fds_pipe[READ_END]);
		dup2(fds_pipe[WRITE_END], STDOUT_FILENO);
		close(fds_pipe[WRITE_END]);
		execlp("/usr/bin/tail", "tail", "-n", "4", NULL);
	}
	else
	{
		close(fds_pipe[WRITE_END]);
		pid = fork();
		if (pid == -1)
		{
			perror("Error en la ejecución de 'fork'.\n");
			exit(ERR_EXECUTING_FORK);
		}
		if (pid == 0)
		{
			flags = O_CREAT | O_WRONLY;
			mode = (S_IRUSR | S_IWUSR) | S_IRGRP | S_IROTH;
			fd_file = open(data.outfile, flags, mode);
			dup2(fd_file, STDOUT_FILENO);
			dup2(fds_pipe[READ_END], STDIN_FILENO);
			close(fds_pipe[READ_END]);
			execlp("/usr/bin/head", "head", "-n", "3", NULL);
		}
		else
		{
			close(fds_pipe[READ_END]);
		}
	}
	wait(&status);
	wait(&status);
}

int	main(int argc, char *argv[])
{
	t_prgdata	data;

	// validate_arguments(argc, argv);
	initialize_program_data(&data, argc, argv);
	show_program_data(data);
	exec_pipex(data);
	release_program_data(data);
	return (0);
}
