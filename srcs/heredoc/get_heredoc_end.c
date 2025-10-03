/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:57:01 by sbalesme          #+#    #+#             */
/*   Updated: 2022/09/22 11:59:13 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static void	get_heredoc_end_bis_two(char *str, \
	char *world, size_t *i, size_t *n)
{
	int	mode;

	mode = 0;
	if (find_char_heredoc(str + *i + 1, '\"', "\\") \
		!= -1 && str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"' || mode == 1)
		{
			if (mode != 0)
			{
				world[(*n)++] = str[(*i)++];
				mode--;
			}
			if (str[*i] == '\\')
			{
				(*i)++;
				mode++;
			}
			else if (str[*i] != '\"' && mode == 0)
				world[(*n)++] = str[(*i)++];
		}
		(*i)++;
	}
}

static void	get_heredoc_end_bis_one(char *str, \
	char *world, size_t *i, size_t *n)
{
	if (find_char_heredoc(str + *i + 1, '\'', "") \
		!= -1 && str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			world[(*n)++] = str[(*i)++];
		(*i)++;
	}
	else
		get_heredoc_end_bis_two(str, world, i, n);
}

static void	get_heredoc_end_bis(char *str, char *world, size_t i, size_t n)
{
	int	mode;

	mode = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\n')
	{
		if (mode != 0)
			mode--;
		if (str[i] == '\\')
		{
			mode++;
			i++;
		}	
		if (mode == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			get_heredoc_end_bis_one(str, world, &i, &n);
		}
		if (mode == 0 && str[i] == ' ')
			break ;
		if (str[i] == '\0' || str[i] == '\n')
			break ;
		world[n++] = str[i++];
	}
	world[n] = '\0';
}

//get the EOF of the heredoc and return the EOF in malloced string
//find the next world in the string and return this world in malloced string
//if the malloc fail return NULL
char	*get_heredoc_end(char *str)
{
	char	*world;

	while (*str != '\0' && *str == ' ')
		str++;
	world = malloc(sizeof(char) * (get_heredoc_end_get_size(str) + 1));
	if (world == NULL)
		return (NULL);
	get_heredoc_end_bis(str, world, 0, 0);
	return (world);
}
