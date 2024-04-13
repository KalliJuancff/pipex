/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:43:22 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/13 19:21:08 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		if (temp == NULL)
			exit_with_internal_error();
		result = ft_strjoin(temp, filename);
		if (result == NULL)
			exit_with_internal_error();
		free(temp);
		if (access(result, F_OK) == 0)
			return (result);
		i++;
	}
	return (result);
}
