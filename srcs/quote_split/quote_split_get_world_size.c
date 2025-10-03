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

static char	*get_world_size_one(char *str, ssize_t *i, ssize_t *res)
{
	int	step;

	if (get_back_slach(str + *i, &step) != -1)
	{
		(*res)++;
		str += step;
	}
	else if (str[*i] == '\'' && find_char(str + *i + 1, '\'') == -1)
		(*i)++;
	else if (str[*i] == '\"' && find_end_quote(str + *i + 1, '\"') == -1)
		(*i)++;
	else if (str[*i] == '\\' && get_back_slach(str + *i, &step) == -1)
	{
		(*res)++;
		if (str[*i] != '\0')
		{
			str++;
			if (str[*i] != '\0')
				str++;
		}
	}
	return (str);
}

static char	*get_world_size_three(char *str, t_info *info, \
	ssize_t *i, ssize_t *res)
{
	char	*tmp;

	tmp = find_world_in_env(str + *i, info, " =$");
	if (tmp != NULL)
		(*res) += ft_strlen(tmp);
	tmp = get_world(str + *i, " =$");
	if (tmp == NULL)
		return (NULL);
	if (tmp[0] == '?')
		str++;
	else
		str += ft_strlen(tmp);
	free(tmp);
	return (str);
}

char	*get_world_size_two(char *str, t_info *info, \
	ssize_t *i, ssize_t *res)
{
	if (str[*i] == '$')
	{
		str++;
		if (str[*i] != '\0' && str[*i] != ' ')
		{
			str = get_world_size_three(str, info, i, res);
			if (str == NULL)
				return (NULL);
		}
		else
		{
			str--;
			(*i)++;
		}
	}
	else
		str = get_world_size_one(str, i, res);
	return (str);
}

static char	*get_world_size_five(char *str, t_info *info, \
	ssize_t *i, ssize_t *res)
{
	char	*tmp;

	str++;
	if (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '\"')
	{
		tmp = find_world_in_env(str + *i, info, "\" =$");
		if (tmp != NULL)
			(*res) += ft_strlen(tmp);
		tmp = get_world(str + *i, "\" =$");
		if (tmp == NULL)
			return (NULL);
		if (tmp[0] == '?')
			str++;
		else
			str += ft_strlen(tmp);
		free(tmp);
	}
	else
	{
		str--;
		(*i)++;
	}
	return (str);
}

char	*get_world_size_four(char *str, t_info *info, \
	ssize_t *i, ssize_t *res)
{
	int	step;

	str++;
	while (str[*i] != '\"')
	{
		if (get_back_slach(str + *i, &step) != -1)
		{
			(*res)++;
			str += step;
			continue ;
		}
		if (str[*i] == '$')
		{
			str = get_world_size_five(str, info, i, res);
			if (str == NULL)
				return (NULL);
		}
		else
			(*i)++;
	}
	str++;
	return (str);
}
