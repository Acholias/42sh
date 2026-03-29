NAME	= 42sh

all:
	@cargo build --release -q
	@cp target/release/$(NAME) .

clean:
	@cargo clean -q

fclean : clean
	@rm -rf $(NAME)

purge: fclean
	@rm -rf ~/.42sh_history

re: fclean all

.PHONY: all clean fclean purge re
