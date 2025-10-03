/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:00:02 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/02 17:54:14 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "minishell.h"

/*pipe.c*/
int		go_pipex(char *args_line, t_info *info, int i);

/*pipe_utils.c*/
char	**copy_args(char **args);

int		free_all_malloc(int *pip, char ***args, int pip_size, int err);

char	*get_first_pipe(t_info *info);

char	*del_first_args_line_pipe(char *args_line);

//get_in_out_pipe.c

int		in_file_pipe(char *args_line, t_info *info, int *fd_in, size_t *i);

char	*out_file_start(char *args_line, t_info *info, \
	int *fd_out, size_t *i);

//get_all_args.c get_all_args_bis.c

int		out_file_pipe(char *args_line, t_info *info, \
	int *fd_out, size_t *i);

void	get_all_args_put_in_pip(int *pip_tmp, int *pip, \
	t_info *info, int pip_size);

void	get_all_args_heredoc(int *pip_tmp, int *pip, \
	t_info *info, int pip_size);

int		get_all_args_start(int *pip_tmp, int i, char ***args, t_info *info);

//create_size_pipe.c

int		*create_size_pipe(char *args_line, int *pipe_size);

//pipe_child.c

void	start_of_child(char *cmd, int *pip, int pip_size, t_info info);

//init_go_pipex.c

int		init_fd_trash(char *args_line, t_info *info);

int		init_pip(char *args_line, int *pip_size, int **pip, t_info *info);

int		init_args(char ****args, int pip_size, int *pip, t_info *info);

char	**get_in_out_file_pip(char *args_line, t_info *info, \
	int *fd_in, int *fd_out);

int		get_all_args(int *pip, char ***args, int pip_size, t_info *info);

//pipe_checker.c

void	start_forking_pipe(char ***args, char **cmd, int *pip, t_info *info);

#endif
