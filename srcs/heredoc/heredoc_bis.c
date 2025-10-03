/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bis.c                                      :+:      :+:    :+:   */
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

static char	**get_pipe_heredoc_bis(char *args_line, char **result)
{
	int		i;
	char	*buf;

	i = 0;
	while (*args_line)
	{
		buf = get_next_line_in_str(args_line);
		if (buf == NULL)
			return (free_args(result, -1));
		result = realloc_heredoc(result, i);
		if (result == NULL)
		{
			free(buf);
			return (NULL);
		}
		result[i] = buf;
		while (*args_line && *args_line != '\n')
			args_line++;
		if (*args_line)
			args_line++;
		i++;
	}
	return (result);
}

char	**get_pipe_heredoc(char *args_line)
{
	char	**result;

	result = malloc(sizeof(char *) * 1);
	if (result == NULL)
		return (NULL);
	result[0] = NULL;
	return (get_pipe_heredoc_bis(args_line, result));
}

static char	**get_pipe_bis(char **pipe_heredoc, int p)
{
	char	*buf;

	while (1)
	{
		buf = readline("pipe> ");
		if (buf == NULL)
			return (free_args(pipe_heredoc, -1));
		if (buf[0] == '\0')
		{
			free(buf);
			continue ;
		}
		pipe_heredoc[p] = buf;
		return (pipe_heredoc);
	}
	return (pipe_heredoc);
}

char	**get_pipe(char **pipe_heredoc, int p)
{
	if (pipe_heredoc == NULL)
	{
		pipe_heredoc = malloc(sizeof(char *) * 2);
		if (pipe_heredoc == NULL)
			return (NULL);
		pipe_heredoc[0] = NULL;
		pipe_heredoc[1] = NULL;
	}
	else
	{
		pipe_heredoc = realloc_heredoc(pipe_heredoc, p);
		if (pipe_heredoc == NULL)
			return (NULL);
	}
	return (get_pipe_bis(pipe_heredoc, p));
}
