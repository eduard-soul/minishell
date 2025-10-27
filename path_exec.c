/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:23:36 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 19:20:09 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_in_path(char *command, char **envp, char **paths, int i)
{
	char	*path;

	if (!(i >= 0))
		return (0);
	paths = ft_split_path(envp[i], ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin_w_char(paths[i], '/', command);
		if (!path)
		{
			free_array(paths);
			return (0);
		}
		if (access(path, X_OK) == 0)
		{
			free_array(paths);
			return (path);
		}
		free(path);
	}
	free_array(paths);
	return (0);
}

void	search_path_and_exec(t_cmds *cmds)
{
	char	*path;
	int		ret;

	path = is_in_path(cmds->argv[0], *(cmds->envp),
			NULL, is_there_a_path(*(cmds->envp)));
	if (!path)
		safe_put_err_n_viable(cmds->envp, cmds->argv[0], ": command not found", 127);
	if (execve(path, cmds->argv, *(cmds->envp)) == -1)
	{
		ret = errno;
		free(path);
		if (ret == EACCES || ret == EISDIR)
			safe_exit(cmds->envp, 126);
		errno = ret;
		perror("execve");
		safe_exit(cmds->envp, 127);
	}
}

void	exec_absolute_path(t_cmds *cmds)
{
	if (access(cmds->argv[0], F_OK) != 0)
		safe_put_err_n_viable(cmds->envp, cmds->argv[0], ": No such file or directory", 127);
	if (is_directory(cmds->argv[0]))
		safe_put_err_n_viable(cmds->envp, cmds->argv[0], ": Is a directory", 126);
	if (access(cmds->argv[0], X_OK) != 0)
		safe_put_err_n_viable(cmds->envp, cmds->argv[0], ": Permission denied", 126);
	if (execve(cmds->argv[0], cmds->argv, *(cmds->envp)) == -1)
	{
		if (errno == EACCES || errno == EISDIR)
			safe_exit(cmds->envp, 126);
		perror("execve");
		safe_exit(cmds->envp, 127);
	}
}
