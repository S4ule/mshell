/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:05:07 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/02 18:35:08 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"
#include "quote_split.h"

//look for '|' at the end of the string
//return 0 if fond
//1 if not fond
int	look_for_pipe_end(char *args_line, int i)
{
	if (i > 0 && args_line[i - 1] == '\n')
		i--;
	while (--i >= 0)
	{
		if (args_line[i] == '|')
			break ;
		if (args_line[i] != ' ')
			return (1);
	}
	return (0);
}

//test the char with charset
//return 0 if the char is fond
//return 1 if the char is not fond
int	test_charset(char c, char *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (0);
		charset++;
	}
	return (1);
}

//check if the string have something before the end
//cherset is use too set end char
// \0 is interpreted all the time
// \n is interpreted all the time
//return 0 if the charset is fond
//return 1 if the charset is not fond
int	check_end(char *str, char *charset)
{
	while (*str && *str != '\n')
	{
		if (test_charset(*str, charset) == 1)
			return (0);
		str++;
	}
	return (1);
}

//get the size of args**
static size_t	size_args(char **args)
{
	size_t	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

//get the next info->pipe_heredoc
//and delet the first line in the pile
//return the line deleted
char	*get_next_pipe_heredoc(t_info *info)
{
	char	**copy;
	char	*output;
	size_t	size;

	size = size_args(info->pipe_heredoc);
	if (size == 0)
		return (NULL);
	copy = malloc(sizeof(char *) * size);
	if (copy == NULL)
		return (NULL);
	while (size > 0)
	{
		copy[size - 1] = info->pipe_heredoc[size];
		size--;
	}
	output = info->pipe_heredoc[0];
	free(info->pipe_heredoc);
	info->pipe_heredoc = copy;
	return (output);
}
