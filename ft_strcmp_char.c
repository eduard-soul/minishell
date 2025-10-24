/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:44:59 by edtataru          #+#    #+#             */
/*   Updated: 2025/09/18 14:56:29 by edtataru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_char(char *s1, char *s2, char delimiter)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] != delimiter && s1[i] == s2[i])
		i++;
	if (!s1[i] || s1[i] == delimiter)
		return (0);
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}
