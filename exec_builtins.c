/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:20:58 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 19:11:56 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	exec_builtin_impl(char **argv, int fd, char ***envp,
						int is_child, t_cmds *cmds)
{
	if (!argv || !argv[0])
		safe_exit_with_cmds(cmds, 127);
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo_ultra(argv, fd));
	if (!ft_strcmp(argv[0], "exit"))
	{
		if (cmds)
			check_and_close_fds(cmds);
		return (ft_exit(argv, is_child, cmds));
	}
	if (!ft_strcmp(argv[0], "export"))
		return (ft_export(argv, envp));
	if (!ft_strcmp(argv[0], "unset"))
		return (ft_unset(argv, envp, 1));
	if (!ft_strcmp(argv[0], "pwd"))
		return (ft_pwd_ultra(fd));
	if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd_ultra(envp, argv));
	if (!ft_strcmp(argv[0], "env"))
		return (ft_env(*envp, fd));
	return (0);
}

int	exec_builtin(char **argv, int fd, char ***envp, int is_child)
{
	return (exec_builtin_impl(argv, fd, envp, is_child, NULL));
}
