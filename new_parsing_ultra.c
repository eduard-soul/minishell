/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing_ultra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:21:33 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/28 20:21:42 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_failure_and_free(t_cmds **cmds)
{
	while ((*cmds)->previous)
		*cmds = (*cmds)->previous;
	free_all_commands(*cmds);
	return (0);
}

int	process_command_segment(char *str, size_t *i, t_cmds **cmds)
{
	if (!store_args(str, *i, (*cmds)->argv)
		|| !store_redirections(str, i, (*cmds)->redirections))
		return (handle_failure_and_free(cmds));
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] == '|')
		(*i)++;
	return (1);
}

int	add_and_setup_cmd(char *str, size_t i, t_cmds **cmds,
		char ***envp)
{
	if (!add_elem_to_cmds(cmds, nb_x_until_pipe(str, i, 1),
			nb_x_until_pipe(str, i, 0), envp))
	{
		if (*cmds)
			return (handle_failure_and_free(cmds));
		return (0);
	}
	(*cmds)->std_input = 0;
	while (*cmds && (*cmds)->next)
		*cmds = (*cmds)->next;
	return (1);
}

t_cmds	*new_parsing_ultra(char **str, t_cmds *cmds, char ***envp,
			int last_ret)
{
	size_t	i;

	if (!search_and_replace_var(str, *envp, last_ret, 0))
		return (0);
	i = 0;
	while ((*str)[i])
	{
		if (!add_and_setup_cmd(*str, i, &cmds, envp))
			return (0);
		if (!process_command_segment(*str, &i, &cmds))
			return (0);
	}
	while (cmds && cmds->previous)
		cmds = cmds->previous;
	return (cmds);
}
