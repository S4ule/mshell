/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:16:21 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/07 01:22:47 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>

# include "get_next_line.h"
# include "libft.h"

typedef struct s_info
{
	char				**env;
	char				**args;
	char				*args_line;
	char				**heredoc;
	char				**eof;
	char				**pipe_heredoc;
	int					fd_in;
	int					fd_out;
	int					fd_trash;
	char				*error;
	int					err;
	int					id;
	int					i;
	int					state;
	int					m_status;
	char				*tmp;
	char				*buf;
	pid_t				g_pid;
}	t_info;

/*
main.c
*/
void	main_loop(t_info *info);

//quote_split call
char	**quote_split(char *str, t_info *info);
char	*find_in_env(char *str, t_info *info, char *charset);

//find the next world in the string and return this world in malloced string
//if the malloc fail return NULL
char	*get_world(char *str, char *charset);

//heredoc
char	**heredoc(char *args_line, t_info *info, size_t i, int n);
int		get_heredoc_fd(t_info *info, int num);

ssize_t	find_char_heredoc(char *str, char c, char *charset);

/*
utils.c
*/
char	*prompt(void);
int		ft_strcmp(const char *s1, const char *s2);
int		mini_strcmp(char *s1, char *s2);
char	**free_args(char **args, ssize_t size);
int		check_j(int j, t_info *info);

//create and add the line in the history
int		add_history_readline(t_info *info);
int		init_all(t_info *info, char **ev);

/*
utils.check
*/
int		check_if_not_empty(char *args_line);
int		check_if_path(char *args_line);
int		is_file(const char *path);
int		check_and_result(char *str, int index, t_info *info);
int		check_and_resultt(char *str, int index, t_info *info);

/*
args.c
*/
int		check_args_line(char *str, t_info *info);
int		ft_perror_and_args(const char *str, int err, t_info *info);

/*
error.c
*/
void	ft_perror_and_print(const char *str, unsigned char err, t_info *info);
int		ft_perror(const char *str, int err, t_info *info);
char	*set_error(t_info *info, int err);
void	check_perm(t_info *info, char *path, int error);

/*
builtin
*/
//cd.c
int		go_cd(t_info *info);
int		gogo_pwd(t_info *info);
int		go_directory(t_info *info, char *path, int free_or_not);
//echo.c
int		go_echo(t_info *info);
//env_utils.c
size_t	env_count(t_info *info);
char	**realloc_env(size_t size, t_info *info);
ssize_t	find_index_env(char *env, t_info *info);
int		setpwd_env(char *env, char *new_env, t_info *info);
//env.c
int		go_env(t_info *info);
char	*get_env(char *env, t_info *info);
void	free_tmp(char *tmp, char *tmpp);
char	*return_tmp(char *tmpp);
//exit.c
int		go_exit(t_info *info, char *cmd);
//export_utils.c
void	ft_sort_env(t_info *info);
void	printf_export(char **env_dup);
//export.c
int		go_export(t_info *info);
//pwd.c
int		go_pwd(t_info *info);
//unset.c
int		go_unset(t_info *info);
//utils.c
int		check_if_builtin(char *cmd);
void	start_builtin(char *cmd, t_info *info);
int		check_cd_error(t_info *info);
int		repertory(t_info *info);

/*
sig.c
*/
void	go_sig(int sig);
void	new_prompt(int sig);
void	ctrl_kill(int sig);
void	bslash(int sig);

/*
get_cmd.h
*/
int		look_for_pipe_end(char *args_line, int i);
int		ignore_quote(char *args_line, size_t *i);

#endif
