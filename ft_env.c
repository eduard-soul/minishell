/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:20:54 by edtataru          #+#    #+#             */
/*   Updated: 2025/07/21 13:04:02 by edtataru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_name_good(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (!is_good_env_char(str[0], 1))
		return (0);
	i++;
	while (str[i])
	{
		if (!is_good_env_char(str[i], 0))
			return (0);
		i++;
	}
	return (1);
}

int	ft_env(char **envp, int fd)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		ft_putstr_fd(envp[i++], fd);
		ft_putstr_fd("\n", fd);
	}
	return (0);
}
