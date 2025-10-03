/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:05:07 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/02 17:56:16 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"
#include "quote_split.h"

static void	ignore_quote_bis(char *args_line, \
	size_t *res, int *j, int *i)
{
	if (find_char_heredoc(args_line + *i + *j + 1, '\'', "\\") != \
		-1 && args_line[*i + *j] == '\'')
	{
		(*j)++;
		while (args_line[*i + *j] != '\'')
		{
			(*i)++;
			(*res)++;
		}
		(*j)++;
	}
	else if (find_end_quote(args_line + *i + *j + 1, '\"') != \
		-1 && args_line[*i + *j] == '\"')
	{
		(*res) += find_end_quote(args_line + *i + *j + 1, '\"');
		(*i) += find_end_quote(args_line + *i + *j + 1, '\"');
		(*j) += 2;
	}
	else
	{
		(*i)++;
		(*res)++;
	}
}

//skip the quote in args_line
//incremente &i with the number of char skiped
//return the number of quote
int	ignore_quote(char *args_line, size_t *res)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (args_line[i + j] && (args_line[i + j] == '\'' || \
		args_line[i + j] == '\"'))
	{
		ignore_quote_bis(args_line, res, &j, &i);
	}
	return (j);
}

static void	copy_world_with_quote_bis(char *str, \
	char *world, size_t *i, size_t *j)
{
	if (find_char_heredoc(str + *i + 1, '\'', "\\") != -1 && str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			world[(*j)++] = str[(*i)++];
		(*i)++;
	}
	else if (find_char_heredoc(str + *i + 1, '\"', "\\") != \
		-1 && str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"')
			world[(*j)++] = str[(*i)++];
		(*i)++;
	}
	else
		world[(*j)++] = str[(*i)++];
}

static char	*copy_world_with_quote(char *str, char *world, char *charset)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == '\'' || str[i] == '\"')
		{
			copy_world_with_quote_bis(str, world, &i, &j);
		}
		if (str[i] == '\0' || test_charset(str[i], charset) == 0)
			break ;
		world[j++] = str[i++];
	}
	world[j] = '\0';
	return (world);
}

//get the next world in malloced string and return the world
//that interprette quote and return the world WITH NO QUOTE
//return null if fail
char	*get_world_with_quote(char *str, char *charset)
{
	char	*world;
	size_t	i;

	i = 0;
	while (*str && *str == ' ')
		str++;
	while (str[i])
	{
		i += ignore_quote(str + i, &i);
		if (str[i] == '\0' || test_charset(str[i], charset) == 0)
			break ;
		i++;
	}
	world = malloc(sizeof(char) * (i + 1));
	if (world == NULL)
		return (NULL);
	return (copy_world_with_quote(str, world, charset));
}
