/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:35:54 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/16 23:30:58 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd_ultra(int fd)
{
	char	*path;

	path = malloc(sizeof(char) * (4096 + 1));
	if (!path)
	{
		perror("pwd error malloc");
		return (127);
	}
	if (getcwd(path, 4096) == NULL)
	{
		perror("pwd cmd error");
		return (127);
	}
	ft_putstr_fd(path, fd);
	ft_putstr_fd("\n", fd);
	free(path);
	return (0);
}