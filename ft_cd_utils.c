/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:03:02 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 14:07:30 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_count(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

char	**copy_env(char **envp)
{
	char	**cpy;
	int		len;
	int		i;

	len = 0;
	while (envp && envp[len])
		len++;
	cpy = malloc(sizeof(char *) * (len + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cpy[i] = ft_strdup(envp[i]);
		if (!cpy[i])
		{
			while (i > 0)
				free(cpy[--i]);
			free(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[len] = NULL;
	return (cpy);
}

int	set_var(char ***env_ref, char *key, char *value)
{
	char	**envp;
	char	*entry;
	int		pos;

	envp = *env_ref;
	entry = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!entry)
		return (-1);
	set_var_second_part(entry, key, value);
	pos = find_key(envp, key);
	if (pos >= 0)
	{
		free(envp[pos]);
		envp[pos] = entry;
		return (0);
	}
	if (set_var_third_part(envp, entry, env_ref) == -1)
		return (-1);
	return (0);
}

void	set_var_second_part(char *entry, char *key, char *value)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (key[++i])
		entry[i] = key[i];
	entry[i++] = '=';
	while (value[++j])
		entry[i + j] = value[j];
	entry[i + j] = '\0';
}

int	set_var_third_part(char **envp, char *entry, char ***env_ref)
{
	int		i;
	int		pos;
	char	**tmp;

	i = 0;
	while (envp && envp[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
	{
		free(entry);
		return (-1);
	}
	pos = -1;
	while (++pos < i)
		tmp[pos] = envp[pos];
	tmp[pos] = entry;
	tmp[pos + 1] = NULL;
	free(envp);
	*env_ref = tmp;
	return (1);
}
