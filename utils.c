/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:03:45 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/23 20:05:11 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_exit(char ***envp, int ret)
{
	if (envp && *envp)
		free_array(*envp);
	exit(ret);
}

void	perror_and_exit(char *str, int ret)
{
	perror(str);
	exit(ret);
}

void	safe_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	check_and_close_fds(t_cmds *cmds)
{
	if (cmds->std_input > 0)
		close(cmds->std_input);
	if (cmds->previous)
	{
		safe_close(cmds->previous->fd[0]);
		safe_close(cmds->previous->fd[1]);
	}
	if (cmds->next)
	{
		safe_close(cmds->fd[0]);
		safe_close(cmds->fd[1]);
	}
}

char	**copy_array_string(char **array)
{
	int		len;
	char	**array_copy;

	len = 0;
	while (array[len])
		len++;
	array_copy = malloc(sizeof(char *) * (len + 1));
	if (!array_copy)
		return (0);
	len = 0;
	while (array[len])
	{
		array_copy[len] = ft_strdup(array[len]);
		if (!array_copy[len])
		{
			while (len--)
				free(array_copy[len]);
			free(array_copy);
			return (0);
		}
		len++;
	}
	array_copy[len] = NULL;
	return (array_copy);
}
