/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:48:17 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/01 17:58:20 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"
#include "pipe.h"

char	**copy_args(char **args)
{
	int		i;
	char	**res;

	if (args == NULL)
		return (NULL);
	i = 0;
	while (args[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (args[i])
	{
		res[i] = args[i];
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	free_all_malloc(int *pip, char ***args, int pip_size, int err)
{
	int	i;

	i = 0;
	while (i < pip_size * 2)
	{
		close(pip[i]);
		i++;
	}
	free(pip);
	i = 0;
	while (args && args[i])
	{
		args[i] = free_args(args[i], -1);
		i++;
	}
	free(args);
	return (err);
}

char	*get_first_pipe(t_info *info)
{
	size_t	i;
	char	*res;

	i = 0;
	while (info->args_line[i] && info->args_line[i] != '|')
	{
		i += ignore_quote(info->args_line + i, &i);
		if (info->args_line[i] && info->args_line[i] != '|')
			i++;
	}
	res = malloc(sizeof(char) * (i + 1));
	if (res == NULL)
		return (NULL);
	res[0] = info->args_line[0];
	res[i] = '\0';
	while (--i > 0)
		res[i] = info->args_line[i];
	info->args_line = del_first_args_line_pipe(info->args_line);
	return (res);
}

static char	*del_first_args_line_pipe_line(char *args_line, size_t i, size_t j)
{
	char	*res;

	res = malloc(sizeof(char) * (j + 1));
	if (res == NULL)
	{
		free(args_line);
		return (NULL);
	}
	j = 0;
	while (args_line[i])
		res[j++] = args_line[i++];
	res[j] = '\0';
	free(args_line);
	return (res);
}

char	*del_first_args_line_pipe(char *args_line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (args_line == NULL)
		return (NULL);
	while (args_line[i] && args_line[i] != '|')
	{
		i += ignore_quote(args_line + i, &i);
		if (args_line[i] && args_line[i] != '|')
			i++;
	}
	while (args_line[i] && (args_line[i] == ' ' || args_line[i] == '|'))
		i++;
	while (args_line[i + j])
		j++;
	if (j == 0)
	{
		free(args_line);
		return (NULL);
	}
	return (del_first_args_line_pipe_line(args_line, i, j));
}
