# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/28 20:16:23 by lumugot           #+#    #+#              #
#    Updated: 2026/03/28 20:27:03 by lumugot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 42sh

all:
	@cargo build --release -q
	@cp target/release/$(NAME) .

clean:
	@cargo clean -q

fclean : clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
