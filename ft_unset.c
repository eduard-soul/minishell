/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:02:57 by edtataru          #+#    #+#             */
/*   Updated: 2025/09/29 15:37:11 by edtataru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_env_index(char **envp, char *key)
{
	int	index;

	if (!envp || !key)
		return (-1);
	index = 0;
	while (envp[index])
	{
		if (!ft_strcmp_char(envp[index], key, '='))
			return (index);
		index++;
	}
	return (-1);
}

static void	remove_env_entry(char **envp, int index)
{
	int	i;

	if (!envp || index < 0 || !envp[index])
		return ;
	free(envp[index]);
	i = index;
	while (envp[i + 1])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}

int	ft_unset(char **argv, char ***envp_ref, int i)
{
	int		status;
	int		index;
	char	**envp;

	if (!argv || !envp_ref || !*envp_ref)
		return (0);
	status = 0;
	while (argv[i])
	{
		if (!is_env_name_good(argv[i]))
		{
			fprintf(stderr, "minishell: unset: `%s': not a valid identifier\n",
				argv[i]);
			status = 1;
		}
		else
		{
			envp = *envp_ref;
			index = find_env_index(envp, argv[i]);
			if (index >= 0)
				remove_env_entry(envp, index);
		}
		i++;
	}
	return (status);
}
