/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var_cmds_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:50:03 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/28 19:17:06 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_escape_char(char **str, size_t *i)
{
	int	j;

	j = *i - 1;
	while ((*str)[++j])
		(*str)[j] = (*str)[j + 1];
	(*i)++;
	return (1);
}

int	handle_single_quotes(char **str, size_t *i)
{
	(*i)++;
	while ((*str)[*i] && (*str)[*i] != '\'')
		(*i)++;
	if ((*str)[*i])
		(*i)++;
	return (1);
}

t_cmds	*init_cmd_elem(char ***envp, int size_argv, int size_redir)
{
	t_cmds	*tmp;

	tmp = malloc(sizeof(t_cmds));
	if (!tmp)
		return (NULL);
	tmp->envp = envp;
	tmp->argv = malloc(sizeof(char *) * (size_argv + 1));
	if (!tmp->argv)
		return (free_and_null(&tmp));
	tmp->redirections = malloc(sizeof(char *) * (size_redir + 1));
	if (!tmp->redirections)
	{
		free_and_null(tmp->argv);
		return (free_and_null(tmp));
	}
	tmp->fd[0] = -1;
	tmp->fd[1] = -1;
	tmp->std_input = 0;
	return (tmp);
}

void	link_cmd_elem(t_cmds **cmds, t_cmds *tmp)
{
	while (*cmds && (*cmds)->next)
		*cmds = (*cmds)->next;
	if (*cmds)
	{
		(*cmds)->next = tmp;
		tmp->previous = *cmds;
	}
	else
		tmp->previous = NULL;
	tmp->next = NULL;
}
