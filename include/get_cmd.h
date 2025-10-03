/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:42:49 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/03 12:27:39 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_CMD_H
# define GET_CMD_H

# include "minishell.h"
# include "heredoc.h"
# include "pipe.h"

//that the cmd
//look the path of cmd if you can't access to cmd
//that gona get path in env and return cmd with the cmd
//if that fail too or malloc fail return NULL
char	*get_cmd(char **args, t_info *info);

void	start_cmd(char **args, char *cmd, t_info info);

int		check_error_cmd(char **args, char *cmd, t_info *info);

int		free_all_go_cmd(char **args, t_info *info);

//pars the args_line
//get the info->fd_in and info->fd_out
//after that the fonction call get_clean_args
//return NULL if that fail in one part
char	**get_in_out_file(char *args_line, t_info *info);

int		get_in_out_file_out(char *args_line, t_info *info, size_t *i);

int		get_in_out_file_in(char *args_line, t_info *info, size_t *i);

ssize_t	get_size_clean_args(char *args_line);

char	*get_clean_args_bis(char *args_line, char *line);

//get clean args create a string with args_line with no doc
//exp : "cat test << test > res"
//to : "cat test  "
//after that call quote_split
//that gonna split that line to get :
// [0] "cat"
// [1] "test"
// [2] NULL
//return NULL if fail in one part
char	**get_clean_args(char *args_line, t_info *info);

//interprete the world in str with charset
//that gonna get the world with the get_world_with_quote() fonction call
//and after that is str in not at the end of
//the str and look for some unexpected token
//return NULL if malloc fail
char	*world_interpreter(char *str, char *charset, t_info *info);

//start of the fonction call
//that pars the args_line and pipe_heredoc
//too call cmd_start and pipex with args
int		pars_cmd(char *args_line, t_info *info);

//skip the quote in args_line
//incremente &i with the number of char skiped
//return the number of quote
int		ignore_quote(char *args_line, size_t *i);

//look for '|' at the end of the string
//return 0 if fond
//1 if not fond
int		look_for_pipe_end(char *args_line, int i);

//get the next info->pipe_heredoc
//and delet the first line in the pile
//return the line deleted
char	*get_next_pipe_heredoc(t_info *info);

//check if the string have something before the end
//cherset is use too set end char
// \0 is interpreted all the time
//return 0 if the charset is fond
//return 1 if the charset is not fond
int		check_end(char *str, char *charset);

//test the char with charset
//return 0 if the char is fond
//return 1 if the char is not fond
int		test_charset(char c, char *charset);

char	*get_world_with_quote(char *str, char *charset);

//start of the fonction call for exev one cmd
int		go_cmd(char *args_line, t_info *info, int err);

#endif
