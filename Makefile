# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/05 17:45:47 by lumugot           #+#    #+#              #
#    Updated: 2026/01/08 17:42:08 by lumugot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 42sh
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -Iincludes
DEBUG_FLAGS	= -DDEBUG
SRCDIR		= srcs
OBJSDIR		= obj

RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
MAGENTA		= \033[0;35m
WHITE		= \033[1;37m
NC			= \033[0m
BOLD		= \033[1m

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

LEXER_SRCS		= token_utils.c \
				  operators.c \
				  quotes.c \
				  tokenizer.c \
				  token_debug.c

PARSER_SRCS		= parser.c \
				  nodes.c \
				  grammar.c \
				  redirections.c \
				  parser_utils.c \
				  free_parser.c

SRCS		= $(addprefix $(SRCDIR)/terminal/, $(TERMINAL_SRCS)) \
			  $(addprefix $(SRCDIR)/line_editing/, $(LINE_EDIT_SRCS)) \
			  $(addprefix $(SRCDIR)/history/, $(HISTORY_SRCS)) \
			  $(addprefix $(SRCDIR)/lexer/, $(LEXER_SRCS)) \
			  $(addprefix $(SRCDIR)/parser/, $(PARSER_SRCS))

OBJS		= $(OBJSDIR)/main.o $(SRCS:$(SRCDIR)/%.c=$(OBJSDIR)/%.o)

TOTAL_FILES	= $(words $(OBJS))
COMPILED	= 0

all: banner $(NAME) success

banner:
	@clear
	@echo ""
	@echo "$(RED)       ▄▄▄    ▄▄▄▄▄              ▄▄       $(NC)"
	@echo "$(RED)      ▄███   █▀▀▀▀██▄            ██       $(NC)"
	@echo "$(RED)     █▀ ██         ██  ▄▄█████▄  ██▄████▄ $(NC)"
	@echo "$(RED)   ▄█▀  ██       ▄█▀   ██▄▄▄▄▄ ▀  ██▀   ██ $(NC)"
	@echo "$(RED)   ████████    ▄█▀      ▀▀▀▀██▄  ██    ██ $(NC)"
	@echo "$(RED)        ██   ▄██▄▄▄▄▄  █▄▄▄▄▄██  ██    ██ $(NC)"
	@echo "$(RED)        ▀▀   ▀▀▀▀▀▀▀▀   ▀▀▀▀▀▀   ▀▀    ▀▀ $(NC)"
	@echo ""
	@echo "$(WHITE)╔════════════════════════════════════════════╗$(NC)"
	@echo "$(WHITE)║            💀  DEVELOPED BY  💀            ║$(NC)"
	@echo "$(WHITE)╠════════════════════════════════════════════╣$(NC)"
	@echo "$(WHITE)║              🤡  Acholias  🤡              ║$(NC)"
	@echo "$(WHITE)╚════════════════════════════════════════════╝$(NC)"
	@echo ""
	@echo "$(BOLD)$(RED)      ◢◤◢◤◢◤  42SH PROJECT SETUP  ◢◤◢◤◢◤$(NC)"
	@echo ""
	@echo "$(MAGENTA)[i]$(NC) Compiling source files..."

$(NAME): $(OBJS)
	@echo ""
	@echo "$(MAGENTA)[i]$(NC) Linking object files..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)[✓]$(NC) Binary created: $(BOLD)./42sh$(NC)"

success:
	@echo ""
	@echo "$(BOLD)$(GREEN)╔══════════════════════════════════════════════╗$(NC)"
	@echo "$(BOLD)$(GREEN)║  ✓ 42sh compilation completed successfully   ║$(NC)"
	@echo "$(BOLD)$(GREEN)║                                              ║$(NC)"
	@echo "$(BOLD)$(GREEN)║  $(YELLOW)Ready to execute: $(BOLD)./42sh$(GREEN)                    ║$(NC)"
	@echo "$(BOLD)$(GREEN)╚══════════════════════════════════════════════╝$(NC)"
	@echo ""

$(OBJSDIR)/main.o: main.c | $(OBJSDIR)
	@printf "    $(YELLOW)→$(NC) Compiling main.c\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/terminal/%.o: $(SRCDIR)/terminal/%.c | $(OBJSDIR)/terminal
	@printf "    $(YELLOW)→$(NC) Compiling terminal/$*.c\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/line_editing/%.o: $(SRCDIR)/line_editing/%.c | $(OBJSDIR)/line_editing
	@printf "    $(YELLOW)→$(NC) Compiling line_editing/$*.c\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/history/%.o: $(SRCDIR)/history/%.c | $(OBJSDIR)/history
	@printf "    $(YELLOW)→$(NC) Compiling history/$*.c\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/lexer/%.o: $(SRCDIR)/lexer/%.c | $(OBJSDIR)/lexer
	@printf "    $(YELLOW)→$(NC) Compiling lexer/$*.c\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/parser/%.o: $(SRCDIR)/parser/%.c | $(OBJSDIR)/parser
	@printf "    $(YELLOW)→$(NC) Compiling parser/$*.c\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR) $(OBJSDIR)/terminal $(OBJSDIR)/line_editing $(OBJSDIR)/history $(OBJSDIR)/lexer $(OBJSDIR)/parser:
	@mkdir -p $@

clean:
	@echo "$(YELLOW)[i]$(NC) Cleaning object files..."
	@rm -rf $(OBJSDIR)
	@echo "$(GREEN)[✓]$(NC) Clean complete"

fclean: clean
	@echo "$(YELLOW)[i]$(NC) Removing binary and history..."
	@rm -rf $(NAME)
	@rm -rf ~/.42sh_history
	@echo "$(GREEN)[✓]$(NC) Full clean complete"

re: fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re debug banner success
