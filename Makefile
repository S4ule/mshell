NAME	  =		minishell
SRC_DIR   = 	srcs
OBJ_DIR   = 	.objs
OBJ_DIRQ  =		.objs/quote_split
OBJ_DIRH  =		.objs/heredoc
OBJ_DIRB  =		.objs/builtin
OBJ_DIRP  =		.objs/pipe
OBJ_DIRG  =		.objs/get_cmd

LIBFT_DIR = 	libft
GNL_DIR	  = 	gnl

LIBFT 	  = 	$(LIBFT_DIR)/libft.a
GNL 	  = 	$(GNL_DIR)/libget_next_line.a

SRC=			$(SRC_DIR)/sig.c\
				$(SRC_DIR)/utils.c\
				$(SRC_DIR)/init.c\
				$(SRC_DIR)/main.c\
				$(SRC_DIR)/error.c\
				$(SRC_DIR)/args.c\
				$(SRC_DIR)/utils_check.c\
				$(SRC_DIR)/quote_split/quote_split.c\
				$(SRC_DIR)/quote_split/quote_split_utils.c\
				$(SRC_DIR)/quote_split/quote.c\
				$(SRC_DIR)/quote_split/quote_split_get_size.c\
				$(SRC_DIR)/quote_split/quote_split_add_world.c\
				$(SRC_DIR)/quote_split/quote_split_add_world_bis.c\
				$(SRC_DIR)/quote_split/quote_split_get_world_size.c\
				$(SRC_DIR)/heredoc/heredoc.c\
				$(SRC_DIR)/heredoc/heredoc_utils.c\
				$(SRC_DIR)/heredoc/add_history_readline.c\
				$(SRC_DIR)/heredoc/heredoc_bis.c\
				$(SRC_DIR)/heredoc/get_heredoc.c\
				$(SRC_DIR)/heredoc/utils.c\
				$(SRC_DIR)/heredoc/get_heredoc_end.c\
				$(SRC_DIR)/heredoc/get_heredoc_end_get_size.c\
				$(SRC_DIR)/heredoc/put_in_heredoc.c\
				$(SRC_DIR)/heredoc/create_line_heredoc.c\
				$(SRC_DIR)/heredoc/create_line_heredoc_bis.c\
				$(SRC_DIR)/heredoc/create_line_heredoc_bis_utils.c\
				$(SRC_DIR)/builtin/echo.c\
				$(SRC_DIR)/builtin/env.c\
				$(SRC_DIR)/builtin/unset.c\
				$(SRC_DIR)/builtin/cd.c\
				$(SRC_DIR)/builtin/utils.c\
				$(SRC_DIR)/builtin/pwd.c\
				$(SRC_DIR)/builtin/export.c\
				$(SRC_DIR)/builtin/env_utils.c\
				$(SRC_DIR)/builtin/export_utils.c\
				$(SRC_DIR)/builtin/exit.c\
				$(SRC_DIR)/pipe/new_pipe.c\
				$(SRC_DIR)/pipe/new_pipe_utils.c\
				$(SRC_DIR)/pipe/get_in_out_pipe.c\
				$(SRC_DIR)/pipe/get_all_args.c\
				$(SRC_DIR)/pipe/get_all_args_bis.c\
				$(SRC_DIR)/pipe/create_size_pipe.c\
				$(SRC_DIR)/pipe/pipe_child.c\
				$(SRC_DIR)/pipe/init_go_pipex.c\
				$(SRC_DIR)/pipe/pipe_checker.c\
				$(SRC_DIR)/get_cmd/get_cmd.c\
				$(SRC_DIR)/get_cmd/get_cmd_utils.c\
				$(SRC_DIR)/get_cmd/get_cmd_utils_bis.c\
				$(SRC_DIR)/get_cmd/go_cmd.c\
				$(SRC_DIR)/get_cmd/check_error_go_cmd.c\
				$(SRC_DIR)/get_cmd/go_cmd_child.c\
				$(SRC_DIR)/get_cmd/go_cmd_utils.c\
				$(SRC_DIR)/get_cmd/get_in_out_file_in.c\
				$(SRC_DIR)/get_cmd/get_in_out_file_out.c\
				$(SRC_DIR)/get_cmd/get_size_clean_args.c\
				$(SRC_DIR)/get_cmd/get_clean_args.c\
				$(SRC_DIR)/get_cmd/grab_get_cmd.c

OBJ		  =		$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CC		  =		gcc
FLAGS	  =		-Wall -Wextra -Werror -g
HEAD 	  =     -I./include -I./$(LIBFT_DIR) -I./$(GNL_DIR)
LFLAGS    =     -L ./$(LIBFT_DIR) -lft -lreadline
GNLFLAGS  =     -L ./$(GNL_DIR) -lget_next_line
RM        =     /bin/rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(GNL)
		@$(CC) $(OBJ) $(HEAD) $(FLAGS) $(LFLAGS) $(GNLFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
		@mkdir -p $(OBJ_DIR) $(OBJ_DIRQ) $(OBJ_DIRH) $(OBJ_DIRB) $(OBJ_DIRP) $(OBJ_DIRG)
		@$(CC) $(FLAGS) $(HEAD) -c $< -o $@
		@echo "\033[1;32m[OK]\033[0m    \033[1;33mCompiling\033[0m $(<F)"

$(LIBFT):
		@make -C $(LIBFT_DIR)
		@make -C $(GNL_DIR)

clean:
		@make clean -C $(LIBFT_DIR)
		@make clean -C $(GNL_DIR)
		@$(RM) $(OBJ_DIR)

fclean:	clean
		@make fclean -C $(LIBFT_DIR)
		@make fclean -C $(GNL_DIR)
		@$(RM) $(NAME)

re:		fclean all

.PHONY:	re fclean clean all
