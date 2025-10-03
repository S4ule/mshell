/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:52:05 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 09:02:54 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_split.h"

//get the size of world in char *str
//return the size of the world
ssize_t	get_world_size(char *str, t_info *info, ssize_t i, ssize_t res)
{
	while (str[i] != '\0' && str[i] != ' ')
	{
		while (str[i] != '\0' && str[i] != ' ' && str[i] != '\"' \
			&& str[i] != '\'' && str[i] != '$' && str[i] != '\\')
			i++;
		if (str[i] == '\'' && find_char(str + i + 1, '\'') != -1)
		{
			str++;
			while (str[i] != '\'')
				i++;
			str++;
		}
		else if (str[i] == '\"' && find_end_quote(str + i + 1, '\"') != -1)
			str = get_world_size_four(str, info, &i, &res);
		else
			str = get_world_size_two(str, info, &i, &res);
		if (str == NULL)
			return (-1);
	}
	return (res + i);
}

//get the world and put in args
//return args
//args is == at NULL if one malloc failed in one place
char	**add_world(char *str, char **args, t_info *info, int i)
{
	int		y;

	y = 0;
	info->i = i;
	if (get_world_size(str, info, 0, 0) == -1)
		return (NULL);
	args[i] = malloc(sizeof(char) * (get_world_size(str, info, 0, 0) + 1));
	if (args[i] == NULL)
		return (free_args(args, i));
	while (*str != '\0' && *str != ' ')
	{
		while (*str != '\0' && *str != ' ' && *str != '\"' \
			&& *str != '\'' && *str != '$' && *str != '\\')
		{
			args[i][y] = *str;
			y++;
			str++;
		}
		str = add_world_six(str, args, info, &y);
		if (str == NULL)
			return (NULL);
	}
	args[i][y] = '\0';
	return (args);
}

static char	*put_in_args_bis(char *str, char **args, t_info *info, int i)
{
	add_world(str, args, info, i);
	if (args == NULL)
		return (NULL);
	while (*str != '\0' && *str != ' ')
	{
		if (*str == '\'' && find_char(str + 1, '\'') != -1)
		{
			str++;
			while (*str != '\'')
				str++;
			str++;
		}
		else if (*str == '\"' && find_end_quote(str + 1, '\"') != -1)
			str += find_end_quote(str + 1, '\"') + 2;
		else if (*str == '\\')
		{
			str++;
			if (*str != '\0')
				str++;
		}
		else
			str++;
	}
	return (str);
}

//put the world in args
//return args or NULL in malloc fail
char	**put_in_args(char *str, char **args, t_info *info)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && *str == ' ')
			str++;
		if (*str != '\0')
		{
			str = put_in_args_bis(str, args, info, i);
			if (str == NULL)
				return (NULL);
			i++;
		}
	}
	args[i] = NULL;
	return (args);
}

//start of the fonction call
//create args of str split with space and sigle/doble quote
//if needed that fonction get the variable in env ex : $PATH
//only if this is don't in sigle quote
char	**quote_split(char *str, t_info *info)
{
	char	**args;

	if (str == NULL || info == NULL)
		return (NULL);
	args = malloc(sizeof(char *) * (get_size(str) + 1));
	if (args == NULL)
		return (NULL);
	put_in_args(str, args, info);
	return (args);
}
