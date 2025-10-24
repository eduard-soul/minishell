/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 02:24:46 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 02:27:43 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_malloc_len_word(char *str, int i, char delim)
{
	char	*result;
	int		j;

	j = 0;
	while (str[i] && str[i] != delim)
	{
		j++;
		i++;
	}
	result = malloc(sizeof(char) * (j + 1));
	return (result);
}

char	**free_split(char **result, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(result[i++]);
	free(result);
	return (NULL);
}

int	count_words(char *str, char delim)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (str[i])
	{
		while (str[i] && str[i] != delim)
			i++;
		while (str[i] == delim)
			i++;
		nb_words++;
	}
	return (nb_words);
}

int	skip_prefix(char *str, int i)
{
	while (str[i])
	{
		if ((i == 0 && str[i] == 'P')
			|| (i == 1 && str[i] == 'A')
			|| (i == 2 && str[i] == 'T')
			|| (i == 3 && str[i] == 'H')
			|| (i == 4 && str[i] == '='))
			i++;
		else
			break ;
	}
	return (i);
}

int	ft_fill_word(char *dest, char *src, int i, char delim)
{
	int	k;

	k = 0;
	while (src[i] && src[i] != delim)
		dest[k++] = src[i++];
	while (src[i] && src[i] == delim)
		i++;
	dest[k] = '\0';
	return (i);
}
