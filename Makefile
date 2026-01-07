# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/05 17:45:47 by lumugot           #+#    #+#              #
#    Updated: 2026/01/07 00:40:22 by lumugot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 42sh
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -Iincludes
SRCDIR		= srcs
OBJSDIR		= obj

TERMINAL_SRCS	= terminal_init.c \
				  keys.c \
				  display.c \
				  signals.c \
				  readline.c

LINE_EDIT_SRCS	= buffer.c \
				  cursor.c \
				  shortcuts.c \
				  mouvements.c

HISTORY_SRCS	= history.c \
				  persistence.c \
				  search.c

LEXER_SRCS		= tokenize.c

SRCS		= $(addprefix $(SRCDIR)/terminal/, $(TERMINAL_SRCS)) \
			  $(addprefix $(SRCDIR)/line_editing/, $(LINE_EDIT_SRCS)) \
			  $(addprefix $(SRCDIR)/history/, $(HISTORY_SRCS)) \
			  $(addprefix $(SRCDIR)/lexer/, $(LEXER_SRCS))

OBJS		= $(OBJSDIR)/main.o $(SRCS:$(SRCDIR)/%.c=$(OBJSDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJSDIR)/main.o: main.c | $(OBJSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/terminal/%.o: $(SRCDIR)/terminal/%.c | $(OBJSDIR)/terminal
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/line_editing/%.o: $(SRCDIR)/line_editing/%.c | $(OBJSDIR)/line_editing
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/history/%.o: $(SRCDIR)/history/%.c | $(OBJSDIR)/history
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/lexer/%.o: $(SRCDIR)/lexer/%.c | $(OBJSDIR)/lexer
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR) $(OBJSDIR)/terminal $(OBJSDIR)/line_editing $(OBJSDIR)/history $(OBJSDIR)/lexer:
	@mkdir -p $@

clean:
	@rm -rf $(OBJSDIR)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf ~/.42sh_history

re: fclean all

.PHONY: all clean fclean re