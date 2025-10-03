/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:54:08 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 18:53:25 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	*get_heredoc_two(char *buf, char *heredoc)
{
	heredoc = ft_strjoin_and_free(heredoc, buf);
	if (heredoc == NULL)
		return (NULL);
	buf = ft_strjoin(heredoc, "\n");
	if (buf == NULL)
		return (NULL);
	free(heredoc);
	heredoc = buf;
	return (heredoc);
}

static char	*free_return_osf(char *free_arg, char *output)
{
	free(free_arg);
	return (output);
}

static char	*get_heredoc_one(char *end, char *heredoc)
{
	char	*buf;

	while (1)
	{
		buf = readline("heredoc> ");
		if (buf == NULL)
			return (free_return_osf(heredoc, NULL));
		if (end[0] == '\0')
		{
			if (buf[0] == '\0')
				return (free_return_osf(buf, heredoc));
		}
		else if (ft_strcmp(buf, end) == 0)
		{
			free(buf);
			return (heredoc);
		}
		heredoc = get_heredoc_two(buf, heredoc);
		if (heredoc == NULL)
			return (NULL);
	}
}

//get the heredoc and return malloced string
char	*get_heredoc(char *end, char *heredoc)
{
	if (heredoc == NULL)
	{
		heredoc = malloc(sizeof(char) * 1);
		if (heredoc == NULL)
			return (NULL);
		heredoc[0] = '\0';
	}
	heredoc = get_heredoc_one(end, heredoc);
	return (heredoc);
}
