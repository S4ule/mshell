/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_end_get_size.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:57:01 by sbalesme          #+#    #+#             */
/*   Updated: 2022/09/22 11:59:13 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static void	get_heredoc_end_get_size_one(char *str, \
	size_t *i, size_t *n, int *mode)
{
	if (find_char_heredoc(str + *i + *n + 1, '\"', "\\") \
		!= -1 && str[*i + *n] == '\"')
	{
		(*n)++;
		while (str[*i + *n] != '\"' || *mode == 1)
		{
			if (*mode != 0)
			{
				(*i)++;
				(*mode)--;
			}
			if (str[*i + *n] == '\\')
			{
				(*n)++;
				(*mode)++;
			}
			else if (str[*i + *n] != '\"' && *mode == 0)
				(*i)++;
		}
		(*n)++;
	}
}

static void	get_heredoc_end_get_size_two(char *str, \
	size_t *i, size_t *n, int *mode)
{
	if (*mode == 0 && (str[*i + *n] == '\'' || str[*i + *n] == '\"'))
	{
		if (find_char_heredoc(str + *i + *n + 1, '\'', "") \
			!= -1 && str[*i + *n] == '\'')
		{
			(*n)++;
			while (str[*i + *n] != '\'')
				(*i)++;
			(*n)++;
		}
		else
			get_heredoc_end_get_size_one(str, i, n, mode);
	}
}

size_t	get_heredoc_end_get_size(char *str)
{
	size_t	i;
	size_t	n;
	int		mode;

	i = 0;
	n = 0;
	mode = 0;
	while (str[i + n] != '\0' && str[i + n] != ' ' && str[i + n] != '\n')
	{
		if (mode != 0)
			mode--;
		if (str[i + n] == '\\')
		{
			mode++;
			n++;
		}
		get_heredoc_end_get_size_two(str, &i, &n, &mode);
		if (mode == 0 && str[i + n] == ' ')
			break ;
		if (str[i + n] == '\0' || str[i + n] == '\n')
			break ;
		i++;
	}
	return (i);
}
