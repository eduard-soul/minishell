/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:31:48 by edtataru          #+#    #+#             */
/*   Updated: 2025/06/19 11:35:02 by edtataru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *to_dup)
{
	int		len;
	char	*copy;

	len = ft_strlen(to_dup);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	copy[len--] = '\0';
	while (len >= 0)
	{
		copy[len] = to_dup[len];
		len--;
	}
	return (copy);
}
