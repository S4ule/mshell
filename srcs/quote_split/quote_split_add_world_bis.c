/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split_add_world_bis.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:52:05 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/07 03:16:10 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_split.h"

static char	*add_world_three(char *str, char **args, t_info *info, int *y)
{
	info->tmp = find_world_in_env(str, info, "\" =$");
	if (info->tmp != NULL)
	{
		args[info->i][*y] = '\0';
		ft_strcat(args[info->i], info->tmp);
		(*y) += ft_strlen(info->tmp);
	}
	info->tmp = get_world(str, "\" =$");
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

static char	*add_world_two(char *str, char **args, t_info *info, int *y)
{
	if (*str == '$')
	{
		str++;
		if (*str != '\0' && *str != ' ' && *str != '\"')
		{
			str = add_world_three(str, args, info, y);
			if (str == NULL)
				return (NULL);
		}
		else
		{
			args[info->i][*y] = '$';
			(*y)++;
		}
	}
	else
	{
		args[info->i][*y] = *str;
		(*y)++;
		str++;
	}
	return (str);
}

char	*add_world_one(char *str, char **args, t_info *info, int *y)
{
	int	step;

	str++;
	while (*str != '\"')
	{
		if (get_back_slach(str, &step) != -1)
		{
			args[info->i][*y] = get_back_slach(str, &step);
			if (args[info->i][*y] == 1)
				args[info->i][*y] = '\\';
			(*y)++;
			str += step;
			continue ;
		}
		str = add_world_two(str, args, info, y);
		if (str == NULL)
			return (NULL);
	}
	str++;
	return (str);
}
