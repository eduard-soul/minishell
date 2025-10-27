/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var_and_cmds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:50:03 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/25 14:37:17 by edtataru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_var(char **str, size_t *i, char **envp, int last_ret)
{
	char	*temp;

	(*i)++;
	if (!(*str)[*i] || (*str)[*i] == ' ' || (*str)[*i] == '"'
		|| (*str)[*i] == '\'' || (*str)[*i] == '|'
		|| (*str)[*i] == '<' || (*str)[*i] == '>')
		return (1);
	if ((*str)[*i] == '?')
		temp = replace_with_ret(str, i, last_ret, NULL);
	else
	{
		if (!is_good_env_char((*str)[*i], 1))
			return (1);
		temp = search_in_envp_and_replace(str, i, envp, 0);
	}
	if (!temp)
		return (0);
	if (ft_strcmp(temp, *str))
	{
		free(*str);
		*str = temp;
	}
	else if (temp != *str)
		free(temp);
	return (1);
}

int	search_and_replace_var_double_quotes(char **str,
					size_t *i, char **envp, int last_ret)
{
	int	j;

	(*i)++;
	while ((*str)[(*i)] && ((*str)[(*i)] != '\"'))
	{
		if ((*str)[(*i)] == '\\' && (*str)[(*i) + 1] == '$')
		{
			j = (*i) - 1;
			while ((*str)[++j])
				(*str)[j] = (*str)[j + 1];
			(*i)++;
		}
		else if ((*str)[(*i)] == '$' && !replace_var(str, i, envp, last_ret))
			return (0);
		else
			(*i)++;
	}
	return (1);
}

int	search_and_replace_var(char **str, char **envp, int last_ret, size_t i)
{
	int	j;

	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && (*str)[i + 1] == '$')
		{
			j = i - 1;
			while ((*str)[++j])
				(*str)[j] = (*str)[j + 1];
		}
		else if ((*str)[i] == '$' && !replace_var(str, &i, envp, last_ret))
			return (0);
		else if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '\'')
				i++;
		}
		else if ((*str)[i] == '\"'
			&& (!search_and_replace_var_double_quotes(str, &i, envp, last_ret)))
			return (0);
		if ((*str)[i])
			i++;
	}
	return (1);
}

void	go_to_first_elem(t_cmds **cmds, t_cmds *tmp)
{
	if (!(*cmds))
		(*cmds) = tmp;
	while ((*cmds) && (*cmds)->previous)
		(*cmds) = (*cmds)->previous;
}

t_cmds	*add_elem_to_cmds(t_cmds **cmds, int size_argv, int size_redir,
			char ***envp)
{
	t_cmds	*tmp;

	tmp = malloc(sizeof(t_cmds));
	if (!tmp)
		return (NULL);
	tmp->envp = envp;
	tmp->argv = malloc(sizeof(char *) * (size_argv + 1));
	if (!tmp->argv)
		return (free_and_null(&tmp));
	tmp->redirections = malloc(sizeof(char *) * (size_redir + 1));
	if (!tmp->redirections)
		free_and_null(tmp->argv);
	if (!tmp->redirections)
		return (free_and_null(tmp));
	while (*cmds && (*cmds)->next)
		*cmds = (*cmds)->next;
	if (*cmds)
		(*cmds)->next = tmp;
	if (*cmds)
		tmp->previous = *cmds;
	else
		tmp->previous = NULL;
	tmp->next = NULL;
	go_to_first_elem(cmds, tmp);
	return (*cmds);
}
