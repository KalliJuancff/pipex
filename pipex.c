/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/07 21:27:24 by jfidalgo         ###   ########.fr       */
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

void	exec_pipeline(t_prgdata data)
{
	int	i;
	int	pipefd[2];
	int	pid;
	int	flags;
	int filefd;
	mode_t	mode;
	int	prevReadFd;

	i = 0;
	while (i < data.commands_number)
	{
		if (i == 0)
		{
			pipe(pipefd);
			pid = fork();
			if (pid == 0)
			{
				flags = O_RDONLY;
				filefd = open(data.infile, flags);
				dup2(filefd, STDIN_FILENO);
				close(filefd);
				dup2(pipefd[WRITE_END], STDOUT_FILENO);
				close(pipefd[WRITE_END]);
				close(pipefd[READ_END]);
				// execlp("/usr/bin/tail", "tail", "-n", "4", NULL);
				// execlp("/bin/sh", "sh", "-c", "echo 7", NULL);
				// execlp("/bin/date", "date", NULL);
				execlp("/usr/bin/grep", "grep", "-v", "T", NULL);
			}
			else
			{
				prevReadFd = pipefd[READ_END];
				close(pipefd[WRITE_END]);
			}
		}
		else if (i == (data.commands_number - 1))
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(prevReadFd, STDIN_FILENO);
				close(pipefd[READ_END]);
				close(pipefd[WRITE_END]);
				flags = O_CREAT | O_WRONLY | O_TRUNC;
				mode = (S_IRUSR | S_IWUSR) | S_IRGRP | S_IROTH;
				filefd = open(data.outfile, flags, mode);
				dup2(filefd, STDOUT_FILENO);
				close(filefd);
				// execlp("/usr/bin/head", "head", "-n", "3", NULL);
				// execlp("/usr", "cat", "-e", NULL);
				// execlp("/bin/date", "date", NULL);
				execlp("/usr/bin/wc", "wc", "-l", NULL);
			}
			else
				close(prevReadFd);
		}
		else
		{
			pipe(pipefd);
			pid = fork();
			if (pid == 0)
			{
				dup2(prevReadFd, STDIN_FILENO);
				close(pipefd[READ_END]);
				dup2(pipefd[WRITE_END], STDOUT_FILENO);
				close(pipefd[WRITE_END]);
				// execlp("/bin/sh", "sh", "-c", "echo 7", NULL);
				// execlp("/usr", "cat", "-e", NULL);
				// execlp("/bin/date", "date", NULL);
				// execlp("/bin/sh", "sh", "-c", "echo 18", NULL);
				execlp("/usr/bin/grep", "grep", "O", NULL);
			}
			else
			{
				close(prevReadFd);
				prevReadFd = pipefd[READ_END];
				close(pipefd[WRITE_END]);
			}
		}
		i++;
	}
	while (i < data.commands_number)
	{
		wait(NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_prgdata	data;

	// validate_arguments(argc, argv);
	initialize_program_data(&data, argc, argv);
	// show_program_data(data);
	// execlp("/bin/sh", "sh", "-c", "echo 7", NULL);
	// execlp("/bin", "cat", "-e", NULL);
	exec_pipeline(data);
	release_program_data(data);
	return (0);
}
