/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_line_heredoc_bis.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:54:08 by sbalesme          #+#    #+#             */
/*   Updated: 2022/09/22 11:56:23 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static int	create_line_free(char **heredoc, char *line, int *n, t_info *info)
{
	info->eof = free_args(info->eof, -1);
	heredoc = free_args(heredoc, *n);
	if (line != NULL)
		free(line);
	return (-1);
}

static int	create_line_bis_bis(char **heredoc, \
	char *args_line, char **line, t_info *info)
{
	if (info->eof[info->id] == NULL)
	{
		create_line_one(info, &(info->i), &(info->state), args_line);
		free(*line);
		return (-2);
	}
	info->buf = get_next_line_in_str(args_line + info->i);
	if (info->buf == NULL)
		return (create_line_free(heredoc, *line, &(info->id), info));
	create_line_two(args_line, &(info->i));
	info->tmp = ft_strtrim(info->buf, "\n");
	if (info->tmp == NULL)
	{
		free(info->buf);
		return (create_line_free(heredoc, *line, &(info->id), info));
	}
	info->state = create_line_three(info, &(info->id), \
		info->tmp, info->buf);
	if (info->state == 1)
		return (-2);
	*line = ft_strjoin_and_free(*line, info->buf);
	if (line == NULL)
		return (create_line_free(heredoc, NULL, &(info->id), info));
	return (0);
}

int	create_line_bis(char **heredoc, char *args_line, char **line, t_info *info)
{
	int	err;

	while (args_line[info->i])
	{
		err = create_line_bis_bis(heredoc, args_line, line, info);
		if (err == -2)
			break ;
		else if (err == -1)
			return (-1);
	}
	return (info->state);
}
