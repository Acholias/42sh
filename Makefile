# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/05 17:45:47 by lumugot           #+#    #+#              #
#    Updated: 2026/01/06 00:56:10 by lumugot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 42sh
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I.
SRCDIR		= srcs/term
OBJSDIR		= obj

SRCS		= term_init.c \
			  	keys.c \
				display.c \
				buffer.c \
				cursor.c \
				shortcuts.c \
				mouvements.c \
				signals.c


OBJS		= $(addprefix $(OBJSDIR)/, main.o $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJSDIR)/main.o: main.c | $(OBJSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/%.o: $(SRCDIR)/%.c | $(OBJSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

clean:
	@rm -rf $(OBJSDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
