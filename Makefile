NAME	= 42sh

all:
	@cargo build --release -q
	@cp target/release/$(NAME) .

run: all
	@./42sh
	@clear

clean:
	@cargo clean -q

fclean : clean
	@rm -rf $(NAME)

purge: fclean
	@rm -rf ~/.42sh_history

re: fclean all

.PHONY: all run clean fclean purge re
