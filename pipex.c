/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/12 17:19:59 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_prgdata dt, int ndx);

void	show_program_data(t_prgdata dt)
{
	int	i;

	printf("Infile: %s\n", dt.infile);
	i = 0;
	while (dt.commands[i] != NULL)
	{
		printf("   Cmd. #%02d/%02d: ", i + 1, dt.commands_number);
		printf("%s\n", dt.commands[i]);
		i++;
	}
	printf("Environment variables:\n");
	i = 0;
	while (dt.env_variables[i] != NULL)
	{
		printf("      Var. #%02d: ", i + 1);
		printf("%s\n", dt.env_variables[i]);
		i++;
	}
	printf("Path directories:\n");
	i = 0;
	while (dt.path_dirs[i] != NULL)
	{
		printf("      Path #%02d: ", i + 1);
		printf("%s\n", dt.path_dirs[i]);
		i++;
	}
	printf("Outfile: %s\n", dt.outfile);
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
		// execlp("/usr/bin/grep", "grep", "-v", "T", NULL);
		execute_command(dt, ndx);
	}
	else
	{
		*prev_fd = pipefd[READ_END];
		close(pipefd[WRITE_END]);
	}
}

void	execute_last_command(t_prgdata dt, int ndx, int prev_fd, int *last_pid)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		redirect_last_command(dt, prev_fd);
		// execlp("/usr/bin/wc", "wc", "-l", NULL);
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
		redirect_middle_command(*prev_fd, pipefd);
		// execlp("/usr/bin/grep", "grep", "O", NULL);
		execute_command(dt, ndx);
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
		result = ft_strjoin(temp, filename);
		free(temp);
		if (access(result, F_OK) == 0)
			return (result);
		i++;;
	}
	return (result);
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
		exit_with_custom_error(ERR_FILE_NOT_FOUND, "Fichero no encontrado");
	execve(fullname, args, dt.env_variables);
	exit_with_internal_error();
}

int	main(int argc, char *argv[], char *envp[])
{
	t_prgdata	data;
	int			result;

	if (argc < 5)
		exit_with_custom_error(ERR_INVALID_NUM_PARAMS, "Nº parámetros incorrecto");
	initialize_program_data(&data, argc, argv, envp);
	// show_program_data(data);
	// execute_command(data, 0);  // NOTA IMPORTANTE: OJO, la ejecución finalizará aquí
	// printf("%s\n", expand_filename(data.path_dirs, "kill"));
	// printf("%s\n", expand_filename(data.path_dirs, "rm"));
	// printf("%s\n", expand_filename(data.path_dirs, "man"));
	// printf("%s\n", expand_filename(data.path_dirs, "date"));
	// printf("%s\n", expand_filename(data.path_dirs, "kk_de_la_vaka"));
	result = exec_pipeline(data);
	release_program_data(data);
	return (result);
}
