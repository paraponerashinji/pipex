NAME= pipex
CC= cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFTDIR)
SRCS= main.c
OBJS= $(SRCS:.c=.o)
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
$(LIBFT):
	@make -C $(LIBFTDIR)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
	make clean -C $(LIBFTDIR)
fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)
all: $(NAME)
re: fclean all
.PHONY: clean fclean all re
