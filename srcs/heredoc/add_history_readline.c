/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history_readline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:57:01 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 11:56:19 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	*add_history_readline_one(int *i, char *line)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (*i + 2));
	if (tmp == NULL)
	{
		free(line);
		return (NULL);
	}
	*i = 0;
	while (line[*i])
	{
		tmp[*i] = line[*i];
		(*i)++;
	}
	tmp[*i] = '\n';
	(*i)++;
	tmp[*i] = '\0';
	free(line);
	line = tmp;
	return (line);
}

static char	*add_history_readline_two(int *i, char *line, t_info *info)
{
	char	*tmp;

	tmp = ft_strjoin(line, info->heredoc[*i]);
	free(line);
	if (tmp == NULL)
		return (NULL);
	line = ft_strjoin(tmp, info->eof[*i]);
	free(tmp);
	if (line == NULL)
		return (NULL);
	tmp = ft_strjoin(line, "\n");
	free(line);
	if (tmp == NULL)
		return (NULL);
	line = tmp;
	(*i)++;
	return (line);
}

static char	*add_history_readline_three(int *i, char *line, t_info *info)
{
	char	*tmp;

	tmp = ft_strjoin(line, info->pipe_heredoc[*i]);
	free(line);
	if (tmp == NULL)
		return (NULL);
	line = tmp;
	if (info->pipe_heredoc[*i][ft_strlen(info->pipe_heredoc[*i]) - 1] != '\n')
	{
		tmp = ft_strjoin(line, "\n");
		free(line);
		if (tmp == NULL)
			return (NULL);
		line = tmp;
	}
	(*i)++;
	return (line);
}

static char	*add_history_readline_four(int *i, char *line, t_info *info)
{
	if (line[*i] == '\0' && \
		(info->heredoc != NULL || info->pipe_heredoc != NULL))
	{
		line = add_history_readline_one(i, line);
		if (line == NULL)
			return (NULL);
	}
	(*i) = 0;
	while (info->heredoc != NULL && info->eof != \
		NULL && info->heredoc[*i] != NULL)
	{
		line = add_history_readline_two(i, line, info);
		if (line == NULL)
			return (NULL);
	}
	(*i) = 0;
	while (info->pipe_heredoc != NULL && info->pipe_heredoc[*i] != NULL)
	{
		line = add_history_readline_three(i, line, info);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

char	*add_history_readline_five(t_info *info)
{
	int		i;
	char	*line;
	char	*tmp;

	line = get_next_line_in_str(info->args_line);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	line = add_history_readline_four(&i, line, info);
	tmp = ft_strtrim(line, "\n");
	free(line);
	if (tmp == NULL)
		return (NULL);
	line = tmp;
	return (line);
}
