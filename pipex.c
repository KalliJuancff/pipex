/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/04 11:48:05 by jfidalgo         ###   ########.fr       */
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
	data->commands = (char **) malloc((count + 1) * sizeof(char *));
	i = 0;
	while (i < count)
	{
		data->commands[i] = argv[i + 2];
		i++;
	}
	data->commands[i] = NULL;
}

void	release_program_data(t_prgdata *data)
{
	free(data->commands);
}

int	main(int argc, char *argv[])
{
	t_prgdata	data;
	int			i;

	validate_arguments(argc, argv);
	initialize_program_data(&data, argc, argv);
	printf(" Infile: %s\n", data.infile);
	i = 0;
	while (data.commands[i] != NULL)
	{
		printf("Cmd. #%d: %s\n", i + 1, data.commands[i]);
		i++;
	}
	printf("Outfile: %s\n", data.outfile);
	release_program_data(&data);
	return (0);
}
