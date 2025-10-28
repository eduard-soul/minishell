/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_and_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:10:03 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/28 20:10:15 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_copies(char *copy, char *original_copy)
{
	if (copy == original_copy)
		free(original_copy);
	else if (copy)
		free(copy);
}

int	free_copy_and_return_code(char *copy, char *original_copy, int ret)
{
	free_copies(copy, original_copy);
	return (ret);
}

void	free_copy_and_exit_code(char *copy, char *original_copy, t_cmds *cmds)
{
	free_copies(copy, original_copy);
	free_all_commands(cmds);
	exit(1);
}

t_cmds	*parse_and_prepare(char **copy, char ***envp_copy,
		int last_ret)
{
	t_cmds	*cmds;

	cmds = new_parsing_ultra(copy, NULL, envp_copy, last_ret);
	if (!cmds)
		return (NULL);
	if (!prepare_pipes(cmds))
		return (NULL);
	while (cmds->previous)
		cmds = cmds->previous;
	return (cmds);
}

int	process_and_run(char *str, char ***envp_copy, int last_ret)
{
	t_cmds	*cmds;
	char	*copy;
	char	*original_copy;
	int		ret;

	add_history(str);
	copy = ft_strdup(str);
	if (!copy)
		return (1);
	original_copy = copy;
	cmds = parse_and_prepare(&copy, envp_copy, last_ret);
	if (!cmds)
		return (free_copy_and_return_code(copy, original_copy, last_ret));
	free_copies(copy, original_copy);
	ret = fork_and_exec_commands(cmds);
	free_all_commands(cmds);
	return (ret);
}
