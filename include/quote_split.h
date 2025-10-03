/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:17:22 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/07 03:17:04 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_SPLIT_H
# define QUOTE_SPLIT_H

# include "minishell.h"

/*
--------------------------------------------------------------------------------
quote_split
--------------------------------------------------------------------------------
*/

/*
quote.c
*/
ssize_t	find_char(char *str, char c);
ssize_t	find_end_quote(char *str, char c);

/*
quote_split_utils.c
*/
char	*find_in_env(char *str, t_info *info, char *charset);
char	*find_world_in_env(char *str, t_info *info, char *charset);
char	get_back_slach(char *str, int *step);

/*
quote_split.c
*/

ssize_t	get_world_size(char *str, t_info *info, \
	ssize_t i, ssize_t res);

char	**add_world(char *str, char **args, t_info *info, int i);

/*
quote_split_get_size.c
*/
size_t	get_size(char *str);

/*
quote_split_add_world.c
*/
char	**add_world(char *str, char **args, t_info *info, int i);

char	*add_world_one(char *str, char **args, t_info *info, int *y);

char	*add_world_six(char *str, char **args, t_info *info, int *y);

/*
quote_split_get_world_size.c
*/

char	*get_world_size_two(char *str, t_info *info, \
	ssize_t *i, ssize_t *res);

char	*get_world_size_four(char *str, t_info *info, \
	ssize_t *i, ssize_t *res);

#endif
