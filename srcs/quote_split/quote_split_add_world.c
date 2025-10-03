/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split_add_world.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:52:05 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/07 03:16:38 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_split.h"

static char	*add_world_five(char *str, char **args, t_info *info, int *y)
{
	int	step;

	if (*str == '\"' && find_end_quote(str + 1, '\"') == -1)
	{
		args[info->i][*y] = *str;
		(*y)++;
		str++;
	}
	else if (*str == '\\' && get_back_slach(str, &step) == -1)
	{
		if (*(str + 1) == '\0')
			args[info->i][*y] = *str;
		else
			args[info->i][*y] = *(str + 1);
		(*y)++;
		if (*str != '\0')
		{
			str++;
			if (*str != '\0')
				str++;
		}
	}
	return (str);
}

char	*add_world_four(char *str, char **args, t_info *info, int *y)
{
	int	step;

	if (get_back_slach(str, &step) != -1)
	{
		args[info->i][*y] = get_back_slach(str, &step);
		(*y)++;
		str += step;
	}
	else if (*str == '\'' && find_char(str + 1, '\'') == -1)
	{
		args[info->i][*y] = *str;
		(*y)++;
		str++;
	}
	else
		str = add_world_five(str, args, info, y);
	return (str);
}

static char	*add_world_eight(char *str, char **args, t_info *info, int *y)
{
	info->tmp = find_world_in_env(str, info, " =$");
	if (info->tmp != NULL)
	{
		args[info->i][*y] = '\0';
		ft_strcat(args[info->i], info->tmp);
		(*y) += ft_strlen(info->tmp);
	}
	info->tmp = get_world(str, " =$");
	if (info->tmp == NULL)
	{
		args = free_args(args, info->i);
		return (NULL);
	}
	if (info->tmp[0] == '?')
		str++;
	else
		str += ft_strlen(info->tmp);
	free(info->tmp);
	return (str);
}

static char	*add_world_seven(char *str, char **args, t_info *info, int *y)
{
	str++;
	if (*str != '\0' && *str != ' ')
	{
		str = add_world_eight(str, args, info, y);
		if (str == NULL)
			return (NULL);
	}
	else
	{
		args[info->i][*y] = '$';
		(*y)++;
	}
	return (str);
}

char	*add_world_six(char *str, char **args, t_info *info, int *y)
{
	if (*str == '\'' && find_char(str + 1, '\'') != -1)
	{
		str++;
		while (*str != '\'')
		{
			args[info->i][*y] = *str;
			(*y)++;
			str++;
		}
		str++;
	}
	else if (*str == '\"' && find_end_quote(str + 1, '\"') != -1)
		str = add_world_one(str, args, info, y);
	else if (*str == '$')
		str = add_world_seven(str, args, info, y);
	else
		str = add_world_four(str, args, info, y);
	if (str == NULL)
		return (NULL);
	return (str);
}
