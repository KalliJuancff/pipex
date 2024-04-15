/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:21:40 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/15 09:35:12 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
static void	show_program_data(t_prgdata dt)
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
*/

static int	execute_pipeline(t_prgdata dt)
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

int	main(int argc, char *argv[], char *envp[])
{
	t_prgdata	data;
	int			result;

	if (argc < 5)
		exit_with_custom_error(ERR_INVALID_NUM_PARAMS,
			"Número de parámetros incorrecto");
	init_program_data(&data, argc, argv, envp);
	result = execute_pipeline(data);
	release_program_data(data);
	return (result);
}
