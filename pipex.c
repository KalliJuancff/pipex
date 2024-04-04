/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/04 10:28:48 by jfidalgo         ###   ########.fr       */
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

// TODO: ren. function name "create_program_data" to, by ex., "initialize_(...)"
// TODO: ren. param name "result" to, by ex., "data"
void	create_program_data(t_prgdata *result, int argc, char *argv[])
{
	int			count;
	int			i;

	result->infile = argv[1];
	result->outfile = argv[argc - 1];
	count = argc - 2 - 1;
	result->cmddata = (t_cmddata **) malloc((count + 1) * sizeof(t_cmddata *));
	i = 0;
	while (i < count)
	{
		result->cmddata[i] = create_command_data(argv, i + 2);
		i++;
	}
	result->cmddata[i] = NULL;
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
	create_program_data(&data, argc, argv);
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
