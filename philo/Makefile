SRCS		= philosophers.c\
				utils.c\
				philo.c\
				time.c\
				cardiac_monitor.c\
				waitress.c\
				initialization.c\
				exit.c

OBJS		= ${SRCS:%.c=$(OBJS_DIR)%.o}
OBJS_DIR	= objects/
NAME		= philo
CC			= cc
WFLAGS		= -Wall -Werror -Wextra
LIBS		= -pthread
RM			= rm -rf

$(OBJS_DIR)%.o:	%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -g -c $< -o $@ -I includes

all:		$(NAME)

$(NAME):	$(OBJS)
			@${CC} $(OBJS) -o $(NAME) $(LIBS)

clean:
			@$(RM) $(OBJS_DIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

test:		re
			@./$(NAME)

.PHONY:		all clean fclean re
