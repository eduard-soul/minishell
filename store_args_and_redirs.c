/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_args_and_redirs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:56:27 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/25 14:41:05 by edtataru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_with_ret(char **str, size_t *i, int last_ret)
{
	char	*dest;
	char	*temp;
	char	*nb;

	dest = ft_strncpy(*str, 0, (*i - 1));
	if (!dest)
		return (0);
	nb = ft_atoi(last_ret);
	if (!nb)
		free(dest);
	if (!nb)
		return (0);
	temp = ft_strjoin(dest, nb);
	free(nb);
	free(dest);
	if (!temp)
		return (0);
	dest = temp;
	temp = ft_strncpy(*str, *i + 1, ft_strlen(*str) - *i);
	if (temp)
		nb = ft_strjoin(dest, temp);
	else
		nb = 0;
	free(dest);
	return (nb);
}

int	store_args(char *str, int i, char **argv)
{
	size_t	j;
	int	failed_malloc;

	j = 0;
	failed_malloc = 0;
	while (str[i] && str[i] != '|')
	{
		(argv)[j] = copy_if_arg(str, &i, &failed_malloc);
		if (failed_malloc)
		{
			i = 0;
			while ((size_t)i != j)
				free(argv[i++]);
			return (0);
		}
		if ((argv)[j])
			j++;
	}
	(argv)[j] = NULL;
	return (1);
}

int	store_redirections(char *str, size_t *i, char **redirections)
{
	size_t	j;

	j = 0;
	while (str[*i] && str[*i] != '|')
	{
		(redirections)[j] = copy_if_redirection(str, i);
		if ((redirections)[j])
			j++;
	}
	(redirections)[j] = NULL;
	return (1);
}
