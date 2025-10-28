/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:12:58 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/28 16:22:07 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_exit(char ***envp, int ret)
{
	if (envp && *envp)
		free_array(*envp);
	exit(ret);
}

void	safe_exit_with_cmds(t_cmds *cmds, int ret)
{
	t_cmds	*first;
	char	***envp;

	if (cmds)
	{
		first = cmds;
		while (first->previous)
			first = first->previous;
		envp = first->envp;
		free_all_commands(first);
		safe_exit(envp, ret);
	}
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

void	safe_close_both_fds(int fd1, int fd2)
{
	safe_close(fd1);
	safe_close(fd2);
}
