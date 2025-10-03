/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clean_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:59:36 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/03 12:27:13 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"

static void	get_clean_args_bis_one(char *args_line, \
	char *line, size_t *i, size_t *j)
{
	if (args_line[*i] == '\'' || args_line[*i] == '\"')
	{
		if (find_char_heredoc(args_line + *i + 1, '\'', "\\") != \
			-1 && args_line[*i] == '\'')
		{
			line[(*j)++] = args_line[(*i)++];
			while (args_line[*i] != '\'')
				line[(*j)++] = args_line[(*i)++];
			line[(*j)++] = args_line[(*i)++];
		}
		else if (find_char_heredoc(args_line + *i + 1, '\"', "\\") != \
			-1 && args_line[*i] == '\"')
		{
			line[(*j)++] = args_line[(*i)++];
			while (args_line[*i] != '\"')
				line[(*j)++] = args_line[(*i)++];
			line[(*j)++] = args_line[(*i)++];
		}
		else
			line[(*j)++] = args_line[(*i)++];
	}
}

static void	get_clean_args_bis_two_bis(char *args_line, size_t *i)
{
	while (args_line[*i + 2] && args_line[*i + 2] == ' ')
		(*i)++;
	while (args_line[*i + 2])
	{
		(*i) += ignore_quote(args_line + *i + 2, i);
		if (args_line[*i + 2] == '\0' || args_line[*i + 2] == ' ')
			break ;
		(*i)++;
	}
	(*i) += 2;
}

static void	get_clean_args_bis_two(char *args_line, \
	char *line, size_t *i, size_t *j)
{
	if (args_line[*i + 1] == '<' || args_line[*i + 1] == '>')
		get_clean_args_bis_two_bis(args_line, i);
	else
	{
		while (args_line[*i + 1] && args_line[*i + 1] == ' ')
			(*i)++;
		while (args_line[*i + 1])
		{
			(*i) += ignore_quote(args_line + *i + 1, i);
			if (args_line[*i + 1] == '\0' || args_line[*i + 1] == ' ')
				break ;
			(*i)++;
		}
		(*i)++;
	}
	while (args_line[*i] && args_line[*i] == ' ')
		(*i)++;
	line[(*j)++] = ' ';
}

char	*get_clean_args_bis(char *args_line, char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (args_line[i])
	{
		while (args_line[i] && (args_line[i] == ' ' || args_line[i] == '\\'))
			line[j++] = args_line[i++];
		if (args_line[i] == '\0')
			break ;
		get_clean_args_bis_one(args_line, line, &i, &j);
		if (args_line[i] == '<' || args_line[i] == '>')
			get_clean_args_bis_two(args_line, line, &i, &j);
		while (args_line[i] && (args_line[i] == ' ' || args_line[i] == '\\'))
			line[j++] = args_line[i++];
		if (args_line[i] != '\0' && args_line[i] != '<' && args_line[i] != '>')
			line[j++] = args_line[i++];
	}
	line[j] = '\0';
	return (line);
}
