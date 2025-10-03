/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:07:47 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/06 10:00:25 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//free the args with size if size != -1
//or free all the args
//return args NULL pointer
char	**free_args(char **args, ssize_t size)
{
	int	i;

	i = 0;
	if (args == NULL)
		return (NULL);
	if (size == -1)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
	else
	{
		while (i < size)
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
	args = NULL;
	return (args);
}

//prompt the shell line and return the line of the user
char	*prompt(void)
{
	char	*args_line;

	args_line = readline("\033[0;36m\033[1m$> \033[0m");
	return (args_line);
}

//strings compare
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (unsigned char)*s1 == (unsigned char)*s2)
	{
		s1++;
		s2++;
	}
	if ((unsigned char)*s1 != (unsigned char)*s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

//strings compare and return booleen if true
int	mini_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	if (ft_strcmp(s1, s2) == 0)
		return (1);
	else
		return (0);
}

int	check_j(int j, t_info *info)
{
	if (j == 4)
	{
		ft_perror_and_args(" syntax error near unexpected token `<'\n", 2, info);
		return (1);
	}
	else if (j == 5)
	{
		ft_perror_and_args(\
		" syntax error near unexpected token `<<'\n", 2, info);
		return (1);
	}
	else if (j >= 6)
	{
		ft_perror_and_args(\
		" syntax error near unexpected token `<<<'\n", 2, info);
		return (1);
	}
	return (0);
}
