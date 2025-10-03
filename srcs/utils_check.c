/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 07:12:51 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/06 09:37:35 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int	check_if_not_empty(char *args_line)
{
	if (args_line == NULL)
		return (1);
	while (*args_line && *args_line == ' ')
		args_line++;
	if (*args_line == '\0')
		return (1);
	return (0);
}

int	check_if_path(char *args_line)
{
	if (*args_line == '~' || *args_line == '.')
		return (2);
	if (*args_line == '/')
		return (1);
	return (0);
}

int	is_file(const char *path)
{
	struct stat	path_stat;
	int			res;

	stat(path, &path_stat);
	res = S_ISREG(path_stat.st_mode);
	return (res);
}

int	check_and_result(char *str, int index, t_info *info)
{
	if (str[index] == '|' && !ft_isalpha(str[index + 2]) && str[index] == '\0')
		return (ft_perror_and_args(" command not found\n", 127, info));
	if (str[index] == '"' && str[index + 1] == '|')
		return (ft_perror_and_args(" command not found\n", 127, info));
	if ((str[index] == '|' && str[index + 1] == '\0'))
		return (ft_perror_and_args(" syntax error near unexpected token `|'\n", \
		2, info));
	return (0);
}

int	check_and_resultt(char *str, int index, t_info *info)
{
	if (str[index - 1] == '>')
	{
		ft_perror_and_args(" syntax error near unexpected token `>>'\n", 2, \
		info);
		return (1);
	}
	else
	{
		ft_perror_and_args(" syntax error near unexpected token `newline'\n", 2, \
		info);
		return (1);
	}
	return (0);
}
