/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_initialization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:40:45 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/12 18:12:27 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_program_data(t_prgdata *dt, int argc, char *argv[], char *envp[])
{
	int		count;
	int		i;
	char	*path_value;

	dt->infile = argv[1];
	dt->outfile = argv[argc - 1];
	count = argc - 2 - 1;
	dt->commands = (char **) malloc((count + 1) * sizeof(char *));
	if (dt->commands == NULL)
		exit_with_internal_error();
	dt->commands_number = count;
	i = 0;
	while (i < count)
	{
		dt->commands[i] = argv[i + 2];
		i++;
	}
	dt->commands[i] = NULL;
	dt->env_variables = envp;
	path_value = get_value_of_environment_variable(envp, "PATH");
	dt->path_dirs = get_path_directories(path_value);
}

void	release_program_data(t_prgdata dt)
{
	int	i;

	free(dt.commands);
	i = 0;
	while (dt.path_dirs[i] != NULL)
	{
		free(dt.path_dirs[i]);
		i++;
	}
	free(dt.path_dirs);
}
