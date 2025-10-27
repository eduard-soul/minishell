/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:31:07 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 19:20:16 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_executable_cmds(t_cmds *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		if (cmds->argv && cmds->argv[0])
			count++;
		cmds = cmds->next;
	}
	return (count);
}

t_cmds	*first_executable_cmd(t_cmds *cmds)
{
	while (cmds)
	{
		if (cmds->argv && cmds->argv[0])
			return (cmds);
		if (cmds->std_input > 0)
		{
			close(cmds->std_input);
			cmds->std_input = 0;
		}
		cmds = cmds->next;
	}
	return (NULL);
}

int	prepare_pipes(t_cmds *cmds)
{
	t_cmds	*cur;
	t_cmds	*cleanup;

	cur = cmds;
	while (cur->next)
	{
		if (pipe(cur->fd) == -1)
		{
			perror("pipe");
			cleanup = cmds;
			while (cleanup != cur)
			{
				close(cleanup->fd[0]);
				close(cleanup->fd[1]);
				cleanup = cleanup->next;
			}
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

void	free_all_commands(t_cmds *cmds)
{
	t_cmds	*next;

	while (cmds)
	{
		next = cmds->next;
		if (cmds->std_input > 0)
			close(cmds->std_input);
		if (cmds->argv)
			free_array(cmds->argv);
		if (cmds->redirections)
			free_array(cmds->redirections);
		free(cmds);
		cmds = next;
	}
}
