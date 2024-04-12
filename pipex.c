/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/12 18:15:20 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	main(int argc, char *argv[], char *envp[])
{
	t_prgdata	data;
	int			result;

	if (argc < 5)
		exit_with_custom_error(ERR_INVALID_NUM_PARAMS, "Nº parámetros incorrecto");
	init_program_data(&data, argc, argv, envp);
	result = execute_pipeline(data);
	release_program_data(data);
	return (result);
}
