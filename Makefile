NAME    = minishell
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iinclude -Ilibft -MMD -MP
LIBFT   = libft/libft.a
RL      = -lreadline

SRCS    = $(shell find src -name '*.c')
OBJS    = $(SRCS:.c=.o)
DEPS    = $(OBJS:.o=.d)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RL) -o $@

$(LIBFT):
	$(MAKE) -C libft bonus

-include $(DEPS)

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS) $(DEPS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean $(NAME)
.PHONY: clean fclean re
