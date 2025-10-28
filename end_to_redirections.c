/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_to_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:59:10 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 13:59:26 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_to_redirections(char **red, int which, char ***envp, t_cmds *cmds)
{
	int	fd;
	int	i;
	int	r;

	fd = -1;
	if (!red)
		return (0);
	if (!red[0])
		return (0);
	i = 0;
	while (red[i])
	{
		if (red[i][0] == which)
		{
			r = open_redir(red[i], which, &fd, envp, cmds);
			if (r < 0)
				return (r);
		}
		i++;
	}
	if (fd == -1)
		return (0);
	return (fd);
}
