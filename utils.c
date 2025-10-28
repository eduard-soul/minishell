/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:03:45 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/28 13:14:50 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_and_close_fds(t_cmds *cmds)
{
	t_cmds	*tmp;

	if (cmds->std_input > 0)
	{
		close(cmds->std_input);
		cmds->std_input = 0;
	}
	tmp = cmds;
	while (tmp->previous)
		tmp = tmp->previous;
	while (tmp)
	{
		if (tmp != cmds && tmp->next && tmp->fd[0] > 2)
			safe_close_both_fds(tmp->fd[0], tmp->fd[1]);
		tmp = tmp->next;
	}
	if (cmds->previous)
		safe_close_both_fds(cmds->previous->fd[0], cmds->previous->fd[1]);
	if (cmds->next)
		safe_close_both_fds(cmds->fd[0], cmds->fd[1]);
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
