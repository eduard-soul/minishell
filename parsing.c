/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:36:44 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/28 12:26:09 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int	is_good_env_char(char c, int is_first)
{
	if (c == 0)
		return (0);
	if (is_first)
	{
		if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z') && c != '_')
			return (0);
		return (1);
	}
	if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z')
		&& c != '_' && !(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

char	*replace_in_envp_if_exist(char *envp, char **str, size_t k, size_t *i)
{
	size_t	new_len;
	char	*dest;
	size_t	l;
	size_t	m;

	new_len = ft_strlen(*str) - (1 + k)
		+ (ft_strlen(envp) - (k + 1));
	dest = malloc(sizeof(char) * (new_len + 1));
	if (!dest)
		return (NULL);
	l = 0;
	while (l < (size_t)(*i - 1))
	{
		dest[l] = (*str)[l];
		l++;
	}
	m = k + 1;
	while (envp[m])
		dest[l++] = envp[m++];
	m = *i + k;
	while ((*str)[m])
		dest[l++] = (*str)[m++];
	dest[l] = '\0';
	*i = *i - 1 + (ft_strlen(envp) - (k + 1));
	return (dest);
}

char	*replace_in_envp_if_not_exist(char **str, size_t k, size_t *i)
{
	char	*dest;
	size_t	l;
	size_t	m;
	size_t	new_len;

	while (is_good_env_char((*str)[*i + k], !k))
		k++;
	new_len = ft_strlen(*str) - k - 1;
	dest = malloc(sizeof(char) * (new_len + 1));
	if (!dest)
		return (NULL);
	l = 0;
	while (l < (size_t)(*i - 1))
	{
		dest[l] = (*str)[l];
		l++;
	}
	m = *i + k;
	while ((*str)[m])
		dest[l++] = (*str)[m++];
	dest[l] = '\0';
	*i = *i - 1;
	return (dest);
}

char	*search_in_envp_and_replace(char **str, size_t *i, char **envp,
				size_t j)
{
	char	*dest;
	size_t	k;

	if (!(*str)[*i])
		return (*str);
	while (envp && envp[j])
	{
		k = 0;
		while (envp[j][k] && envp[j][k] != '='
			&& is_good_env_char((*str)[*i + k], !k)
			&& envp[j][k] == (*str)[*i + k])
			k++;
		if (envp[j][k] == '=' && !is_good_env_char((*str)[*i + k], !k))
		{
			dest = replace_in_envp_if_exist(envp[j], str, k, i);
			return (dest);
		}
		j++;
	}
	k = 0;
	return (replace_in_envp_if_not_exist(str, k, i));
}

void	new_parsing_ultra_part2(t_cmds *cmds, char **str, size_t *i, char ***envp)
{
	
		if (!add_elem_to_cmds(&cmds, nb_x_until_pipe(*str, i, 1),
				nb_x_until_pipe(*str, i, 0), envp))
		{
			if (cmds)
			{
				while (cmds->previous)
					cmds = cmds->previous;
				free_all_commands(cmds);
			}
			return (0);
		}
		cmds->std_input = 0;
		while (cmds && cmds->next)
			cmds = cmds->next;
		if (!store_args(*str, i, cmds->argv) || !store_redirections(*str, &i, cmds->redirections))
		{
			while (cmds->previous)
				cmds = cmds->previous;
			free_all_commands(cmds);
			return (0);
		}
		while ((*str)[i] && (*str)[i] == ' ')
			i++;
		if ((*str)[i] == '|')
			i++;
}

t_cmds	*new_parsing_ultra(char **str, t_cmds *cmds, char ***envp,
			int last_ret)
{
	size_t	i;

	if (!search_and_replace_var(str, *envp, last_ret, 0))
		return (0);
	i = 0;
	while ((*str)[i])
	{
	}
	while (cmds && cmds->previous)
		cmds = cmds->previous;
	return (cmds);
}
