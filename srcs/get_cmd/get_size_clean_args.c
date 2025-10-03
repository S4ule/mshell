/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_clean_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:59:36 by sbalesme          #+#    #+#             */
/*   Updated: 2022/09/22 12:04:46 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"

static void	get_size_clean_args_two(char *args_line, size_t *i, int mode)
{
	if (mode == 1)
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
		return ;
	}
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

static void	get_size_clean_args_one(char *args_line, size_t *i, size_t *res)
{
	if (args_line[*i] == '<' || args_line[*i] == '>')
	{
		if (args_line[*i + 1] == '<' || args_line[*i + 1] == '>')
			get_size_clean_args_two(args_line, i, 1);
		else
			get_size_clean_args_two(args_line, i, 2);
		while (args_line[*i] && args_line[*i] == ' ')
			(*i)++;
		(*res)++;
	}
	while (args_line[*i] && (args_line[*i] == ' ' || args_line[*i] == '\\'))
	{
		(*i)++;
		(*res)++;
	}
}

//get the size of the clean_args in get_clean_args
//return -1 if fail to malloc
ssize_t	get_size_clean_args(char *args_line)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (args_line[i])
	{
		while (args_line[i] && (args_line[i] == ' ' || args_line[i] == '\\'))
		{
			res++;
			i++;
		}
		res += ignore_quote(args_line + i, &res);
		i += ignore_quote(args_line + i, &i);
		get_size_clean_args_one(args_line, &i, &res);
		if (args_line[i] && args_line[i] != '<' && args_line[i] != '>')
		{
			res++;
			i++;
		}
	}
	return (res);
}
