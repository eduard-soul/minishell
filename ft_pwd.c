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

/*
int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (s1[i] - s2[i]);
}
*/

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

/*
void	ft_pwd(t_minishell *minishell)
{
	int		i;

	i = 0;
	if (minishell->args)
	{
		while (minishell->args[i] == ' ' || (minishell->args[i] > 8
				&& minishell->args[i] < 13))
			i++;
		if ((minishell->args[i] == '-' && minishell->args[i + 1] != '-') 
			|| (minishell->args[i + 1] == '-' && minishell->args[i + 2] != '\0'))
		{
			write(2, "pwd error option\n", 17);
			minishell->last_ret = 2;
			return ;
		}
	}
	minishell->output_cmd = malloc(sizeof(char) * (4096 + 1));
	if (!minishell->output_cmd)
	{
		write(2, "pwd error malloc\n", 17);
		minishell->last_ret = 2;
		return ; // malloc protected?
	}
	if (getcwd(minishell->output_cmd, 4096) == NULL) // ouais prq pas mdrr
	{
		write(2, "pwd cmd error\n", 14); // maybe not needed
		minishell->last_ret = 2;
		return ;
	}
}
*/
/*
int	main(int argc, char **argv)
{
	(void)argc;
	t_minishell minishell;
	minishell.last_ret = 0;
	minishell.output_cmd = 0;
	minishell.args = argv[1];
	ft_pwd(&minishell);
	printf("%s\n", minishell.output_cmd);
	printf("%d\n", minishell.last_ret);
	return (0);
}
*/
