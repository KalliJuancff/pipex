/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/08 19:21:04 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define READ_END 0
#define WRITE_END 1

void	test_open_and_close(t_prgdata data)
{
	int	flags;
	int	filefd;

	flags = O_RDONLY;
	filefd = open(data.infile, flags);
	if (filefd == -1)
		ft_exit();
	if (close(filefd + 1000) == -1)
		ft_exit();
}

void	show_program_data(t_prgdata data)
{
	int	i;

	printf(" Infile: %s\n", data.infile);
	i = 0;
	while (data.commands[i] != NULL)
	{
		printf("Cmd. #%d / %d: ", i + 1, data.commands_number);
		printf("%s\n", data.commands[i]);
		i++;
	}
	printf("Outfile: %s\n", data.outfile);
}

void	redirect_first_command(t_prgdata data, int pipefd[2])
{
	int	flags;
	int	filefd;

	flags = O_RDONLY;
	filefd = open(data.infile, flags);
	dup2(filefd, STDIN_FILENO);
	close(filefd);
	dup2(pipefd[WRITE_END], STDOUT_FILENO);
	close(pipefd[WRITE_END]);
	close(pipefd[READ_END]);
}

void	redirect_last_command(t_prgdata data, int prev_read_fd)
{
	int		flags;
	mode_t	mode;
	int		filefd;

	dup2(prev_read_fd, STDIN_FILENO);
	close(prev_read_fd);
	flags = O_CREAT | O_WRONLY | O_TRUNC;
	mode = (S_IRUSR | S_IWUSR) | S_IRGRP | S_IROTH;
	filefd = open(data.outfile, flags, mode);
	dup2(filefd, STDOUT_FILENO);
	close(filefd);
}

void	redirect_middle_command(t_prgdata data, int prev_read_fd, int pipefd[2])
{
	dup2(prev_read_fd, STDIN_FILENO);
	close(prev_read_fd);
	dup2(pipefd[WRITE_END], STDOUT_FILENO);
	close(pipefd[WRITE_END]);
	close(pipefd[READ_END]);
}

void	execute_first_command(t_prgdata data, int *prev_read_fd)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		redirect_first_command(data, pipefd);
		execlp("/usr/bin/grep", "grep", "-v", "T", NULL);
	}
	else
	{
		*prev_read_fd = pipefd[READ_END];
		close(pipefd[WRITE_END]);
	}
}

void	execute_last_command(t_prgdata data, int prev_read_fd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		redirect_last_command(data, prev_read_fd);
		execlp("/usr/bin/wc", "wc", "-l", NULL);
	}
	else
		close(prev_read_fd);
}

void	execute_middle_command(t_prgdata data, int *prev_read_fd)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		redirect_middle_command(data, *prev_read_fd, pipefd);
		execlp("/usr/bin/grep", "grep", "O", NULL);
	}
	else
	{
		close(*prev_read_fd);
		*prev_read_fd = pipefd[READ_END];
		close(pipefd[WRITE_END]);
	}
}

void	exec_pipeline(t_prgdata data)
{
	int	i;
	int	prev_read_fd;

	i = 0;
	while (i < data.commands_number)
	{
		if (i == 0)
			execute_first_command(data, &prev_read_fd);
		else if (i == (data.commands_number - 1))
			execute_last_command(data, prev_read_fd);
		else
			execute_middle_command(data, &prev_read_fd);
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
	test_open_and_close(data);
	// show_program_data(data);
	// execlp("/bin/sh", "sh", "-c", "echo 7", NULL);
	// execlp("/bin", "cat", "-e", NULL);
	exec_pipeline(data);
	release_program_data(data);
	return (0);
}
