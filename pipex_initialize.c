/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:40:29 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/07 15:39:42 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_arguments(int argc, char *argv[])
{
	if (argc != 5)
		ft_exit(ERR_NUM_PARAMS_KO);
}

// TODO: Validar que malloc NO devuelva NULL
void	initialize_program_data(t_prgdata *data, int argc, char *argv[])
{
	int			count;
	int			i;

	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	count = argc - 2 - 1;
	data->commands_number = count;
	data->commands = (char **) malloc((count + 1) * sizeof(char *));
	i = 0;
	while (i < count)
	{
		data->commands[i] = argv[i + 2];
		i++;
	}
	data->commands[i] = NULL;
}

void	release_program_data(t_prgdata data)
{
	free(data.commands);
}
