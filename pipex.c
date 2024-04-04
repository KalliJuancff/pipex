/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/04 10:44:35 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_arguments(int argc, char *argv[])
{
	if (argc != 5)
		ft_exit2(ERR_NUM_PARAMS_KO, "Número de parámetros incorrecto");
}

t_cmddata	*create_command_data(char *argv[], int index)
{
	t_cmddata	*result;

	result = (t_cmddata *) malloc(sizeof(t_cmddata));
	result->cmdname = ft_strdup(argv[index]);
	return (result);
}

void	initialize_program_data(t_prgdata *data, int argc, char *argv[])
{
	int			count;
	int			i;

	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	count = argc - 2 - 1;
	data->cmddata = (t_cmddata **) malloc((count + 1) * sizeof(t_cmddata *));
	i = 0;
	while (i < count)
	{
		data->cmddata[i] = create_command_data(argv, i + 2);
		i++;
	}
	data->cmddata[i] = NULL;
}

void	release_command_data(t_cmddata *cmddata)
{
	free(cmddata->cmdname);
	free(cmddata);
}

void	release_program_data(t_prgdata *prgdata)
{
	int	i;

	i = 0;
	while (prgdata->cmddata[i] != NULL)
	{
		release_command_data(prgdata->cmddata[i]);
		i++;
	}
	free(prgdata->cmddata);
}

int	main(int argc, char *argv[])
{
	t_prgdata	data;
	int			i;

	// validate_arguments(argc, argv);
	initialize_program_data(&data, argc, argv);
	printf(" Infile: %s\n", data.infile);
	i = 0;
	while (data.cmddata[i] != NULL)
	{
		printf("Cmd. #%d: %s\n", i + 1, data.cmddata[i]->cmdname);
		i++;
	}
	printf("Outfile: %s\n", data.outfile);
	release_program_data(&data);
	return (0);
}
