/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:17:44 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/07 01:23:36 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"

//do strjoin() and free the two string after that
char	*ft_strjoin_and_free(char *s1, char *s2);

//find the next world in the string and return this world in malloced string
//if the malloc fail return NULL
char	*get_heredoc_end(char *str);

char	*get_next_line_in_str(char *str);

char	*add_history_readline_five(t_info *info);

char	**get_pipe(char **pipe_heredoc, int p);

char	**get_pipe_heredoc(char *args_line);

//get the heredoc and return malloced string
char	*get_heredoc(char *end, char *heredoc);

size_t	get_heredoc_end_get_size(char *str);

char	**put_in_heredoc(char **heredoc, \
	char *args_line, int save, t_info *info);

int		create_line(char **heredoc, char *args_line, int *n, t_info *info);

int		create_line_bis(char **heredoc, \
	char *args_line, char **line, t_info *info);

int		create_line_three(t_info *info, int *n, char *tmp, char *buf);

void	create_line_two(char *args_line, int *i);

void	create_line_one(t_info *info, int *i, int *state, char *args_line);

#endif
