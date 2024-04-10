/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/10 12:56:30 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_program_data(t_prgdata dt)
{
	int	i;

	printf(" Infile: %s\n", dt.infile);
	i = 0;
	while (dt.commands[i] != NULL)
	{
		printf("Cmd. #%d / %d: ", i + 1, dt.commands_number);
		printf("%s\n", dt.commands[i]);
		i++;
	}
	printf("Outfile: %s\n", dt.outfile);
}

void	execute_first_command(t_prgdata dt, int *prev_read_fd)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		redirect_first_command(dt, pipefd);
		execlp("/usr/bin/grep", "grep", "-v", "T", NULL);
	}
	else
	{
		*prev_read_fd = pipefd[READ_END];
		close(pipefd[WRITE_END]);
	}
}

void	execute_last_command(t_prgdata dt, int prev_read_fd, int *last_pid)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		redirect_last_command(dt, prev_read_fd);
		execlp("/usr/bin/wcxyz", "wcxyz", "-l", NULL);
	}
	else
	{
		close(prev_read_fd);
		*last_pid = pid;
	}
}

void	execute_middle_command(t_prgdata dt, int *prev_read_fd)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		redirect_middle_command(*prev_read_fd, pipefd);
		execlp("/usr/bin/grep", "grep", "O", NULL);
	}
	else
	{
		close(*prev_read_fd);
		*prev_read_fd = pipefd[READ_END];
		close(pipefd[WRITE_END]);
	}
}

int	exec_pipeline(t_prgdata dt)
{
	int	i;
	int	prev_read_fd;
	int	last_pid;
	int	status;
	int	result;

	i = 0;
	while (i < dt.commands_number)
	{
		if (i == 0)
			execute_first_command(dt, &prev_read_fd);
		else if (i == (dt.commands_number - 1))
			execute_last_command(dt, prev_read_fd, &last_pid);
		else
			execute_middle_command(dt, &prev_read_fd);
		i++;
	}
	status = 0;
	i = 0;
	while (i++ < dt.commands_number)
	{
		if (wait(&status) == last_pid && WIFEXITED(status))
			result = WEXITSTATUS(status);
	}
	return (result);
}

int	main(int argc, char *argv[])
{
	t_prgdata	data;
	int			result;

	// validate_arguments(argc, argv);
	initialize_program_data(&data, argc, argv);
	// show_program_data(data);
	// execlp("/bin/sh", "sh", "-c", "echo 7", NULL);
	// execlp("/bin", "cat", "-e", NULL);
	result = exec_pipeline(data);
	release_program_data(data);
	return (result);
}
