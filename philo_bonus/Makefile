NAME		:= philo_bonus
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror

SRCS	:= 	main_bonus.c \
			utils_bonus.c \
			init_bonus.c \
			fork_bonus.c \
			monitor_bonus.c \

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re