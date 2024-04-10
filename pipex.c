/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/10 16:09:47 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
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
*/

void	execute_command(char *command)
{
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, "\n", 1);
}

void	execute_first_command(t_prgdata dt, int *prev_fd, int ndx)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		redirect_first_command(dt, pipefd);
		// execlp("/usr/bin/grep", "grep", "-v", "T", NULL);
		execute_command(dt.commands[ndx]);
		exit(0);
	}
	else
	{
		*prev_fd = pipefd[READ_END];
		close(pipefd[WRITE_END]);
	}
}

void	execute_last_command(t_prgdata dt, int prev_fd, int *last_pid, int ndx)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		redirect_last_command(dt, prev_fd);
		// execlp("/usr/bin/wc", "wc", "-l", NULL);
		execute_command(dt.commands[ndx]);
		exit(0);
	}
	else
	{
		close(prev_fd);
		*last_pid = pid;
	}
}

void	execute_middle_command(t_prgdata dt, int *prev_fd, int ndx)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		redirect_middle_command(*prev_fd, pipefd);
		// execlp("/usr/bin/grep", "grep", "O", NULL);
		execute_command(dt.commands[ndx]);
		exit(0);
	}
	else
	{
		close(*prev_fd);
		*prev_fd = pipefd[READ_END];
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
			execute_first_command(dt, &prev_read_fd, i);
		else if (i == (dt.commands_number - 1))
			execute_last_command(dt, prev_read_fd, &last_pid, i);
		else
			execute_middle_command(dt, &prev_read_fd, i);
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

	// if (argc != 5)
	//	exit_with_custom_error(ERR_NUM_PARAMS_KO, "Nº parámetros incorrecto");
	initialize_program_data(&data, argc, argv);
	result = exec_pipeline(data);
	release_program_data(data);
	return (result);
}
