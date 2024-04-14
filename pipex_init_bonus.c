/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:24:46 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/14 12:24:50 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Ejemplo de posible valor de la variable del entorno 'PATH':
//     "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applications/VMware"
char	*get_value_of_environment_variable(char *envp[], char *var_name)
{
	int		i;
	size_t	len;
	int		condition1;
	int		condition2;

	i = 0;
	len = ft_strlen(var_name);
	while (envp[i] != NULL)
	{
		condition1 = (ft_strnstr(envp[i], var_name, len) != NULL);
		condition2 = (envp[i][ft_strlen(var_name)] == '=');
		if (condition1 && condition2)
			return (envp[i] + ft_strlen(var_name) + 1);
		i++;
	}
	return (NULL);
}

// Ejemplo de posible valor del argumento 'path_value':
//     "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applications/VMware"
char	**get_path_directories(char *path_value)
{
	char	**result;

	result = ft_split(path_value, ':');
	if (result == NULL)
		exit_with_internal_error();
	return (result);
}

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
	if (path_value == NULL)
		exit_with_custom_error(ERR_PATH_ENV_VAR_NOT_FOUND,
			"No se encontró la variable del entorno 'PATH'");
	dt->path_dirs = get_path_directories(path_value);
}

void	release_program_data(t_prgdata dt)
{
	int	i;

	if (dt.commands != NULL)
		free(dt.commands);
	if (dt.path_dirs != NULL)
	{
		i = 0;
		while (dt.path_dirs[i] != NULL)
		{
			free(dt.path_dirs[i]);
			i++;
		}
		free(dt.path_dirs);
	}
}
