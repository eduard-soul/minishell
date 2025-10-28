/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:06:22 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/28 16:44:20 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_ws_ptr(char *s)
{
	if (!s)
		return (s);
	while (*s == ' ')
		s++;
	return (s);
}

int	handle_sig_and_empty(char *line, int *last_ret)
{
	if (get_signal_flag())
	{
		*last_ret = 130;
		reset_signal_flag();
		if (!line[0])
		{
			free(line);
			return (1);
		}
	}
	return (0);
}

int	handle_eof(char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (1);
	}
	return (0);
}

int	free_copy_and_return_code(char *copy, char *original_copy, int ret)
{
	if (copy == original_copy)
		free(original_copy);
	else if (copy)
		free(copy);
	return (ret);
}

void	free_copy_and_exit_code(char *copy, char *original_copy, t_cmds *cmds)
{
	if (copy == original_copy)
		free(original_copy);
	else if (copy)
		free(copy);
	free_all_commands(cmds);
	exit(1);
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
	cmds = new_parsing_ultra(&copy, NULL, envp_copy, last_ret);
	if (!cmds)
		return (free_copy_and_return_code(copy, original_copy, last_ret));
	if (!prepare_pipes(cmds))
		free_copy_and_exit_code(copy, original_copy, cmds);
	while (cmds->previous)
		cmds = cmds->previous;
	if (copy == original_copy)
		free(original_copy);
	else if (copy)
		free(copy);
	ret = fork_and_exec_commands(cmds);
	free_all_commands(cmds);
	return (ret);
}
