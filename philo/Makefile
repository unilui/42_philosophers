SRCS		= philosophers.c\
				stages.c\
				utils.c\
				philosopher_th.c\
				time.c\
				cardiac_monitor.c\
				waitress.c\
				initialization.c\
				exit.c\
				args_validation.c

OBJS		= ${SRCS:%.c=$(OBJS_DIR)%.o}
OBJS_DIR	= objects/
NAME		= philo
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
LIBS		= -pthread
RM			= rm -rf

$(OBJS_DIR)%.o:	%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -g -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			@${CC} $(CFLAGS) $(OBJS) -g -o $(NAME) $(LIBS)

clean:
			@$(RM) $(OBJS_DIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

test:		re
			@./$(NAME)

.PHONY:		all clean fclean re
