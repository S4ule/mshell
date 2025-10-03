/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:54:08 by sbalesme          #+#    #+#             */
/*   Updated: 2022/09/22 11:56:23 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	**realloc_heredoc(char **heredoc, int n)
{
	int		i;
	char	**output;

	output = malloc(sizeof(char *) * (n + 2));
	if (output == NULL)
	{
		free(heredoc);
		return (NULL);
	}
	i = 0;
	while (i <= n)
	{
		output[i] = heredoc[i];
		i++;
	}
	output[i] = NULL;
	free(heredoc);
	return (output);
}

static char	**heredoc_fail(char **heredoc, int n, t_info *info)
{
	if (info->eof != NULL)
		info->eof = free_args(info->eof, n);
	if (heredoc != NULL)
		heredoc = free_args(heredoc, n);
	return (NULL);
}

static char	**heredoc_bis(char *args_line, \
	t_info *info, size_t *i, char **heredoc)
{
	char	*end;

	(*i) += ignore_quote(args_line + *i, i);
	if (args_line[*i] != '\0' && args_line[*i] == '<')
	{
		(*i)++;
		if (args_line[*i] == '<')
		{
			(*i)++;
			heredoc = realloc_heredoc(heredoc, info->id);
			if (heredoc == NULL)
				return (heredoc_fail(heredoc, info->id, info));
			info->eof = realloc_heredoc(info->eof, info->id);
			if (info->eof == NULL)
				return (heredoc_fail(heredoc, info->id, info));
			end = get_heredoc_end(args_line + *i);
			if (end == NULL)
				return (heredoc_fail(heredoc, info->id, info));
			info->eof[info->id] = end;
			heredoc[info->id] = NULL;
			info->id += 1;
		}
	}
	return (heredoc);
}

//start of the fonction call
char	**heredoc(char *args_line, t_info *info, size_t i, int n)
{
	char	**heredoc;

	if (args_line == NULL)
		return (NULL);
	heredoc = malloc(sizeof(char *) * 1);
	if (heredoc == NULL)
		return (NULL);
	heredoc[0] = NULL;
	info->eof = malloc(sizeof(char *) * 1);
	if (info->eof == NULL)
		return (heredoc_fail(heredoc, -1, info));
	info->eof[0] = NULL;
	while (args_line[i] && args_line[i] != '\n')
	{
		info->id = n;
		heredoc = heredoc_bis(args_line, info, &i, heredoc);
		if (heredoc == NULL)
			return (NULL);
		n = info->id;
		if (args_line[i] != '\0' && args_line[i] != '\n')
			i++;
	}
	heredoc = put_in_heredoc(heredoc, args_line, n, info);
	return (heredoc);
}
