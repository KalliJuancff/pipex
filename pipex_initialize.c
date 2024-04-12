/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:40:29 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/12 16:13:25 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Ejemplo:
//     "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applications/VMware Fusion.app/Contents/Public"
char	*get_value_of_environment_variable(char *envp[], char *var_name)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], var_name, ft_strlen(var_name)) != NULL && envp[i][ft_strlen(var_name)] == '=')
			return (envp[i] + ft_strlen(var_name) + 1);
		i++;
	}
	exit_with_custom_error(ERR_PATH_ENV_VAR_NOT_FOUND, "No se encontró la variable del entorno 'PATH'");
	return (0);
}

// Ejemplo:
//     "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applications/VMware Fusion.app/Contents/Public"
char	**get_path_directories(char *path_value)
{
	return (ft_split(path_value, ':'));
}

void	initialize_program_data(t_prgdata *dt, int argc, char *argv[], char *envp[])
{
	int	count;
	int	i;

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
	dt->path_dirs = get_path_directories(get_value_of_environment_variable(envp, "PATH"));
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
