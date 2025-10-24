/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:11:07 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/23 22:10:51 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	name_len_until_equal_or_plus(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			break ;
		i++;
	}
	return (i);
}

int	find_key_index(char **envp, char *key)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strcmp_char(envp[i], key, '='))
			return (i);
		i++;
	}
	return (-1);
}

char	*build_assignment(char *key, char *value)
{
	char	*with_equal;
	char	*full;

	with_equal = ft_strjoin(key, "=");
	if (!with_equal)
		return (NULL);
	if (!value)
		return (with_equal);
	full = ft_strjoin(with_equal, value);
	free(with_equal);
	return (full);
}

char	**free_array_and_ret_null(char **arr)
{
	free_array(arr);
	return (NULL);
}

char	**append_to_envp(char **envp, char *to_add)
{
	char	**new_envp;
	int		len_envp;
	int		i;

	len_envp = 0;
	while (envp && envp[len_envp])
		len_envp++;
	new_envp = malloc(sizeof(char *) * (len_envp + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < len_envp)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			return (free_array_and_ret_null(new_envp));
		i++;
	}
	new_envp[i] = ft_strdup(to_add);
	if (!new_envp[i])
		return (free_array_and_ret_null(new_envp));
	new_envp[i + 1] = NULL;
	return (new_envp);
}
