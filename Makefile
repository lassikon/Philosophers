NAME		:= philo
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g #-fsanitize=thread -g -static-libsan

LIBFT	:= $(LIBFT_DIR)/libft.a
SRCS	:= 	main.c \
			utils.c \
			init.c \
			invalid_args.c \
			routine.c \
			threads.c \
			overseer.c \

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