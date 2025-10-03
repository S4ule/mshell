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

static int	create_line_osf(char *s1, char *s2, int *s3, int re)
{
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	if (s3 != NULL)
		free(s3);
	return (re);
}

void	create_line_one(t_info *info, int *i, int *state, char *args_line)
{
	info->pipe_heredoc = get_pipe_heredoc(args_line + (*i));
	(*state) = -2;
	while (args_line[*i] != '\0')
		(*i)++;
}

void	create_line_two(char *args_line, int *i)
{
	while (args_line[*i] && args_line[*i] != '\n')
		(*i)++;
	if (args_line[*i] == '\n')
		(*i)++;
}

int	create_line_three(t_info *info, int *n, char *tmp, char *buf)
{
	if (ft_strcmp(tmp, info->eof[*n]) == 0)
		return (create_line_osf(tmp, buf, NULL, 1));
	free(tmp);
	return (0);
}
