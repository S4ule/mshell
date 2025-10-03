
SRCS	=	get_next_line.c\
			get_next_line_utils.c

OBJ		=	$(SRCS:.c=.o)

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

NAME	=	libget_next_line.a

.c.o:
			@gcc $(CFLAGS) -I . -c $< -o $(<:.c=.o)

all:		$(NAME)
			@echo "\033[1;32m[OK]\033[0m    \033[1;33mCompiling\033[0m $(<F)"

$(NAME):	$(OBJ)
			@ar rcs $(NAME) $(OBJ)


clean:
			@$(RM) $(OBJ)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:	re fclean clean all
