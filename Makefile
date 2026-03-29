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
