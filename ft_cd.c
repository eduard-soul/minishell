/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:55:07 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/23 14:40:08 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_key(char **envp, char *key)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strcmp_char(envp[i], key, '=') == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	update_pwd(char ***envp, char *oldpwd, char *newpwd)
{
	if (oldpwd)
		set_var(envp, "OLDPWD", oldpwd);
	if (newpwd)
		set_var(envp, "PWD", newpwd);
}

int	if_chdir_fail(char *oldpwd, char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd((char *)strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(oldpwd);
		return (1);
	}
	return (0);
}

int	alloc_or_args(char *msg, char *to_free)
{
	if (to_free)
		free(to_free);
	ft_putstr_fd(msg, 2);
	return (1);
}

int	ft_cd_ultra(char ***envp, char **argv)
{
	char	*oldpwd;
	char	*newpwd;
	char	*path;

	if (arg_count(argv) != 2)
		return (alloc_or_args("Minishell: cd: too many arguments\n", NULL));
	path = argv[1];
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup("");
	if (!oldpwd)
		return (alloc_or_args("Minishell: cd: alloc error\n", NULL));
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
