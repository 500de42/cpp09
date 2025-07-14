NAME = btc
FLAG = -Wall -Werror -Wextra -std=c++98
SRCS = main.cpp BitcoinExchange.cpp

all : $(NAME)

$(NAME) : $(SRCS)
	c++ $(FLAG) $(SRCS) -o $(NAME)

clean :

fclean : clean
	rm -rf $(NAME)

re : fclean all
