/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_cmds_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:24:07 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/14 12:24:16 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*expand_filename(char **path_dirs, char *filename)
{
	char	*result;
	int		i;
	char	*temp;

	result = NULL;
	i = 0;
	while (path_dirs[i] != NULL)
	{
		temp = ft_strjoin(path_dirs[i], "/");
		if (temp == NULL)
			exit_with_internal_error();
		result = ft_strjoin(temp, filename);
		if (result == NULL)
			exit_with_internal_error();
		free(temp);
		if (access(result, F_OK) == 0 && access(result, X_OK) == 0)
			return (result);
		free(result);
		i++;
	}
	return (NULL);
}

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
		exit_with_custom_error(ERR_FILE_NOT_FOUND_OR_WITHOUT_PERMISSIONS,
			"Comando no encontrado o sin permisos de ejecución");
	execve(fullname, args, dt.env_variables);
	exit_with_internal_error();
}

void	execute_first_command(t_prgdata dt, int ndx, int *prev_fd)
{
	int	pipefd[2];
	int	pid;

	if (pipe(pipefd) == -1)
		exit_with_internal_error();
	pid = fork();
	if (pid == -1)
		exit_with_internal_error();
	if (pid == 0)
	{
		redirect_first_command(dt, pipefd);
		execute_command(dt, ndx);
	}
	else
	{
		if (close(pipefd[WRITE_END]) == -1)
			exit_with_internal_error();
		*prev_fd = pipefd[READ_END];
	}
}

void	execute_last_command(t_prgdata dt, int ndx, int prev_fd, int *last_pid)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit_with_internal_error();
	if (pid == 0)
	{
		redirect_last_command(dt, prev_fd);
		execute_command(dt, ndx);
	}
	else
	{
		if (close(prev_fd) == -1)
			exit_with_internal_error();
		*last_pid = pid;
	}
}

void	execute_middle_command(t_prgdata dt, int ndx, int *prev_fd)
{
	int	pipefd[2];
	int	pid;

	if (pipe(pipefd) == -1)
		exit_with_internal_error();
	pid = fork();
	if (pid == -1)
		exit_with_internal_error();
	if (pid == 0)
	{
		redirect_middle_command(pipefd, *prev_fd);
		execute_command(dt, ndx);
	}
	else
	{
		if (close(*prev_fd) == -1)
			exit_with_internal_error();
		if (close(pipefd[WRITE_END]) == -1)
			exit_with_internal_error();
		*prev_fd = pipefd[READ_END];
	}
}
