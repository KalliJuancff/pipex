/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execution_commands.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:26:11 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/13 18:26:36 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_prgdata dt, int ndx)
{
	char	*command;
	char	**args;
	char	*command_name;
	char	*fullname;

	command = dt.commands[ndx];
	args = ft_split(command, ' ');
	if (args == NULL)
		exit_with_internal_error();
	command_name = args[0];
	fullname = expand_filename(dt.path_dirs, command_name);
	if (fullname == NULL)
		exit_with_custom_error(ERR_FILE_NOT_FOUND, "Fichero no encontrado");
	execve(fullname, args, dt.env_variables);
	exit_with_internal_error();
}

void	execute_first_command(t_prgdata dt, int ndx, int *prev_fd)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		redirect_first_command(dt, pipefd);
		execute_command(dt, ndx);
	}
	else
	{
		close(pipefd[WRITE_END]);
		*prev_fd = pipefd[READ_END];
	}
}

void	execute_last_command(t_prgdata dt, int ndx, int prev_fd, int *last_pid)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		redirect_last_command(dt, prev_fd);
		execute_command(dt, ndx);
	}
	else
	{
		close(prev_fd);
		*last_pid = pid;
	}
}

void	execute_middle_command(t_prgdata dt, int ndx, int *prev_fd)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		redirect_middle_command(pipefd, *prev_fd);
		execute_command(dt, ndx);
	}
	else
	{
		close(*prev_fd);
		close(pipefd[WRITE_END]);
		*prev_fd = pipefd[READ_END];
	}
}

int	execute_pipeline(t_prgdata dt)
{
	int	i;
	int	prev_read_fd;
	int	last_pid;
	int	status;
	int	result;

	i = 0;
	while (dt.commands[i] != NULL)
	{
		if (i == 0)
			execute_first_command(dt, i, &prev_read_fd);
		else if (i == (dt.commands_number - 1))
			execute_last_command(dt, i, prev_read_fd, &last_pid);
		else
			execute_middle_command(dt, i, &prev_read_fd);
		i++;
	}
	status = 0;
	i = 0;
	while (dt.commands[i++] != NULL)
	{
		if (wait(&status) == last_pid && WIFEXITED(status))
			result = WEXITSTATUS(status);
	}
	return (result);
}
