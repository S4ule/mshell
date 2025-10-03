/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:09:31 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 08:13:18 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_split.h"

//utils for get_world
//copy the world find in world malloced string
static void	copy_world(char *str, char *charset, char *world)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (charset[j] != '\0')
		{
			if (charset[j] == str[i])
				break ;
			j++;
		}
		if (charset[j] != '\0')
			break ;
		else
		{
			world[i] = str[i];
			i++;
		}
	}
	world[i] = '\0';
}

//find the next world in the string and return this world in malloced string
//if the malloc fail return NULL
char	*get_world(char *str, char *charset)
{
	char	*world;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (charset[j] != '\0')
		{
			if (charset[j] == str[i])
				break ;
			j++;
		}
		if (charset[j] != '\0')
			break ;
		else
			i++;
	}
	world = malloc(sizeof(char) * (i + 1));
	if (world == NULL)
		return (NULL);
	copy_world(str, charset, world);
	return (world);
}

static int	count_i(t_info *info, int i)
{
	while (info->env[i] != NULL)
		i++;
	return (i);
}

//find str in env and return env string pointer if find
//return NULL is str is not fond is env
char	*find_in_env(char *str, t_info *info, char *charset)
{
	int		i;
	char	*tmp;

	i = 0;
	if (*str == '?')
		return (info->error);
	while (info->env[i] != NULL)
	{
		tmp = get_world(info->env[i], charset);
		if (tmp == NULL)
		{
			count_i(info, i);
			break ;
		}
		if (ft_strcmp(str, tmp) == 0)
		{
			free(tmp);
			break ;
		}
		free(tmp);
		i++;
	}
	if (info->env[i] == NULL)
		return (NULL);
	return ((info->env[i]) + ft_strlen(str) + 1);
}

//find str first world in env and retrun env string pointer if find
//world is string separate by charset caracter
//return NULL is str first world is not fond is env
char	*find_world_in_env(char *str, t_info *info, char *charset)
{
	char	*tmp;
	char	*str_env;

	tmp = get_world(str, charset);
	if (tmp == NULL)
		return (NULL);
	if (tmp[0] == '\0')
	{
		free(tmp);
		return (NULL);
	}
	str_env = find_in_env(tmp, info, charset);
	free(tmp);
	return (str_env);
}
