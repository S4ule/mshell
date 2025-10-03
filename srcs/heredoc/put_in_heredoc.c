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

static char	**put_in_heredoc_one(t_info *info, int *n, char **heredoc)
{
	(*n) = 0;
	while (info->pipe_heredoc != NULL && info->pipe_heredoc[*n] != NULL)
		(*n)++;
	if (*n > 0 && info->pipe_heredoc != NULL)
		(*n)--;
	while (info->pipe_heredoc != NULL)
	{
		if (look_for_pipe_end(info->pipe_heredoc[*n], \
			ft_strlen(info->pipe_heredoc[*n])) == 1)
			break ;
		info->pipe_heredoc = get_pipe(info->pipe_heredoc, *n + 1);
		if (info->pipe_heredoc == NULL)
		{
			info->eof = free_args(info->eof, -1);
			heredoc = free_args(heredoc, -1);
			return (NULL);
		}
		(*n)++;
	}
	return (heredoc);
}

static char	**put_in_heredoc_two(t_info *info, int *i, \
	char **heredoc, char *args_line)
{
	(*i) = 0;
	while (args_line[*i] && args_line[*i] != '\n')
		(*i)++;
	if (look_for_pipe_end(args_line, *i) == 0)
	{
		if (info->pipe_heredoc == NULL)
		{
			info->pipe_heredoc = get_pipe(info->pipe_heredoc, 0);
			if (info->pipe_heredoc == NULL)
			{
				info->eof = free_args(info->eof, -1);
				heredoc = free_args(heredoc, -1);
				return (NULL);
			}
		}
	}
	return (heredoc);
}

static char	**put_in_heredoc_three(t_info *info, char **heredoc, \
	int *n, int save)
{
	while (*n < save)
	{
		heredoc[*n] = get_heredoc(info->eof[*n], heredoc[*n]);
		if (heredoc[*n] == NULL)
		{
			info->eof = free_args(info->eof, -1);
			heredoc = free_args(heredoc, *n);
			return (NULL);
		}
		(*n)++;
	}
	return (heredoc);
}

char	**put_in_heredoc(char **heredoc, \
	char *args_line, int save, t_info *info)
{
	int	n;
	int	i;
	int	tmp;

	i = 0;
	n = 0;
	while (args_line[i] && args_line[i] != '\n')
		i++;
	if (args_line[i] == '\n')
		i++;
	while (args_line[i])
	{
		tmp = create_line(heredoc, args_line + i, &n, info);
		if (tmp == -1)
			return (NULL);
		i += tmp;
	}
	heredoc = put_in_heredoc_three(info, heredoc, &n, save);
	if (heredoc == NULL)
		return (NULL);
	heredoc = put_in_heredoc_two(info, &i, heredoc, args_line);
	if (heredoc == NULL)
		return (NULL);
	return (put_in_heredoc_one(info, &n, heredoc));
}
