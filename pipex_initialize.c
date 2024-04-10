/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:40:29 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/10 10:21:27 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_arguments(int argc, char *argv[])
{
	if (argc != 5)
		exit_with_custom_error(ERR_NUM_PARAMS_KO, "Número de parámetros incorrecto");
}

void	initialize_program_data(t_prgdata *dt, int argc, char *argv[])
{
	int	count;
	int	i;

	dt->infile = argv[1];
	dt->outfile = argv[argc - 1];
	count = argc - 2 - 1;
	dt->commands_number = count;
	dt->commands = (char **) malloc((count + 1) * sizeof(char *));
	if (dt->commands == NULL)
		exit_with_internal_error();
	i = 0;
	while (i < count)
	{
		dt->commands[i] = argv[i + 2];
		i++;
	}
	dt->commands[i] = NULL;
}

void	release_program_data(t_prgdata dt)
{
	free(dt.commands);
}
