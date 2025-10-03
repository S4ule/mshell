/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_line_heredoc.c                              :+:      :+:    :+:   */
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

int	create_line(char **heredoc, char *args_line, int *n, t_info *info)
{
	char	*line;
	int		state;

	line = malloc(sizeof(char) * 1);
	if (line == NULL)
		return (create_line_free(heredoc, NULL, n, info));
	line[0] = '\0';
	info->id = *n;
	info->i = 0;
	info->state = 0;
	state = create_line_bis(heredoc, args_line, &line, info);
	if (state == -1)
	{
		line = NULL;
		return (-1);
	}
	if (state == 1)
		heredoc[(*n)++] = line;
	else if (state == 0)
	{
		heredoc[*n] = ft_strjoin(line, "\n");
		free(line);
	}
	return (info->i);
}
