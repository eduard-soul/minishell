/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 22:05:50 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 22:11:02 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_or_append(char ***p_envp, char *name, char *value, int idx)
{
	char	*assign;
	char	**new_env;

	idx = find_key_index(*p_envp, name);
	if (idx != -1)
	{
		assign = build_assignment(name, value);
		if (!assign)
			return (1);
		free((*p_envp)[idx]);
		(*p_envp)[idx] = assign;
		return (0);
	}
	assign = build_assignment(name, value);
	if (!assign)
		return (1);
	new_env = append_to_envp(*p_envp, assign);
	if (!new_env)
		free(assign);
	if (!new_env)
		return (1);
	free(assign);
	free_array(*p_envp);
	*p_envp = new_env;
	return (0);
}

int	skip_k(char **p_envp, int i)
{
	int	k;

	k = 0;
	while ((p_envp)[i][k] && (p_envp)[i][k] != '=')
		k++;
	return (k);
}

int	handle_plus_equal(char ***p_envp, char *name, char *value, char *existing)
{
	int		i;
	int		k;
	char	*tmp;
	char	*assign;

	i = find_key_index(*p_envp, name);
	if (i == -1)
		return (replace_or_append(p_envp, name, value, 0));
	k = skip_k(*p_envp, i);
	if ((*p_envp)[i][k] == '=')
	{
		existing = (*p_envp)[i] + k + 1;
		tmp = ft_strjoin(existing, value);
		if (!tmp)
			return (1);
		assign = build_assignment(name, tmp);
		free(tmp);
	}
	else
		assign = build_assignment(name, value);
	if (!assign)
		return (1);
	free((*p_envp)[i]);
	(*p_envp)[i] = assign;
	return (0);
}

int	has_equal_ret(int ret, char ***p_envp, char *name)
{
	ret = handle_no_equal(p_envp, name);
	free(name);
	return (ret);
}
