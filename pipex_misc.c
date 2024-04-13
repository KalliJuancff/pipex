/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:43:22 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/13 18:50:16 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Ejemplo de posible valor de la variable del entorno 'PATH':
//     "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applications/VMware"
// 
// NOTA:
// La última línea, el exit, es simplemente para evitar el warning
//     "non-void function does not return a value in all control paths"
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
	exit_with_custom_error(ERR_PATH_ENV_VAR_NOT_FOUND,
		"No se encontró la variable del entorno 'PATH'");
	return (0);
}

// Ejemplo de posible valor del argumento 'path_value':
//     "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applications/VMware"
char	**get_path_directories(char *path_value)
{
	return (ft_split(path_value, ':'));
}

char	*expand_filename(char **path_dirs, char *filename)
{
	char	*result;
	int		i;
	char	*temp;

	result = NULL;
	i = 0;
	while (path_dirs[i] != NULL)
	{
		temp = ft_strjoin(path_dirs[i], "/");
		result = ft_strjoin(temp, filename);
		free(temp);
		if (access(result, F_OK) == 0)
			return (result);
		i++;
	}
	return (result);
}
