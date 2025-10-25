/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:00:19 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/23 22:12:31 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_copy_envp(char **copy)
{
	int	i;
	int	k;

	i = 0;
	while (copy[i])
	{
		k = 0;
		while (copy[i][k] && copy[i][k] != '=')
			k++;
		if (copy[i][k] == '=')
			printf("export %.*s=\"%s\"\n", k, copy[i], copy[i] + k + 1);
		else
			printf("export %s\n", copy[i]);
		i++;
	}
}

int	print_export_sorted(char **envp, int i, int j)
{
	char	**copy;
	char	*tmp;

	copy = copy_array_string(envp);
	if (!copy)
		return (1);
	while (copy[++i])
	{
		j = i + 1;
		while (copy[j])
		{
			if (ft_strcmp(copy[i], copy[j]) > 0)
			{
				tmp = copy[i];
				copy[i] = copy[j];
				copy[j] = tmp;
			}
			j++;
		}
	}
	print_copy_envp(copy);
	free_array(copy);
	return (0);
}

int	handle_no_equal(char ***p_envp, char *name)
{
	int		idx;
	char	*entry;
	char	**new_env;

	idx = find_key_index(*p_envp, name);
	if (idx != -1)
		return (0);
	entry = build_assignment(name, "");
	if (!entry)
		return (1);
	new_env = append_to_envp(*p_envp, entry);
	if (!new_env)
	{
		free(entry);
		return (1);
	}
	free(entry);
	free_array(*p_envp);
	*p_envp = new_env;
	return (0);
}

int	process_arg(char ***p_envp, char *arg, int is_plus, int len)
{
	int		has_equal;
	char	*name;
	char	*value;

	int (ret) = 0;
	if (arg[len] == '+' && arg[len + 1] == '=')
		is_plus = 1;
	has_equal = 0;
	if (arg[len] == '=' || is_plus)
		has_equal = 1;
	name = ft_strncpy(arg, 0, len);
	if (!name)
		return (1);
	if (!is_env_name_good(name))
		return (put_err_and_free_name(arg, name));
	if (!has_equal)
		return (has_equal_ret(ret, p_envp, name));
	value = arg + len + 1;
	if (is_plus)
		value = arg + len + 2;
	if (is_plus)
		ret = handle_plus_equal(p_envp, name, value, NULL);
	else
		ret = replace_or_append(p_envp, name, value, 0);
	return (free_and_ret(name, ret));
}

int	ft_export(char **argv, char ***envp_ref)
{
	int	ret;
	int	i;

	if (!argv || !envp_ref || !*envp_ref)
		return (1);
	if (!argv[1])
		return (print_export_sorted(*envp_ref, -1, 0));
	ret = 0;
	i = 1;
	while (argv[i])
	{
		if (process_arg(envp_ref, argv[i], 0,
				name_len_until_equal_or_plus(argv[i])))
			ret = 1;
		i++;
	}
	return (ret);
}
