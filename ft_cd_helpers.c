/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:55:07 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/23 14:40:08 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_path(char ***envp)
{
	int		home_idx;
	char	*path;

	home_idx = find_key(*envp, "HOME");
	if (home_idx == -1)
		return (NULL);
	path = ft_strdup((*envp)[home_idx] + 5);
	return (path);
}

int	handle_cd_path(char ***envp, char **argv, char **path)
{
	if (arg_count(argv) == 1)
	{
		*path = get_home_path(envp);
		if (!*path)
			return (alloc_or_args("Minishell: cd: HOME not set\n", NULL));
	}
	else
		*path = argv[1];
	return (0);
}

int	handle_cd_execution(char ***envp, char *path, char *oldpwd)
{
	char	*newpwd;

	if (if_chdir_fail(oldpwd, path))
		return (1);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		newpwd = ft_strdup(path);
	if (!newpwd)
		return (alloc_or_args("Minishell: cd: alloc error\n", oldpwd));
	update_pwd(envp, oldpwd, newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
