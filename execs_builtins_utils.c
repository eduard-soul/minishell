/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_builtins_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:21:44 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 19:14:45 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search_char_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_w_char(char *s1, char c, char *s2)
{
	int		len;
	char	*dest;
	int		i;
	int		j;

	len = ft_strlen(s1) + 1 + ft_strlen(s2);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		dest[j++] = s1[i++];
	dest[j++] = c;
	i = 0;
	while (s2[i])
		dest[j++] = s2[i++];
	dest[j] = '\0';
	return (dest);
}

int	is_there_a_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strcmp_char(envp[i], "PATH", '='))
			return (i);
		i++;
	}
	return (-1);
}

int	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode) != 0);
}

void	put_err_n_viable(char *argv, char *error_msg, int exit_code)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(exit_code);
}
