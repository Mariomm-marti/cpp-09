NAME    = btc
CC      = c++
CFLAGS  = -Wall -Werror -Wextra -std=c++98
DEBUG   = -D __CPP09_DEBUG_=true

SRCS    = BitcoinExchange.cpp \
					main.cpp
OBJS    = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

debug: $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
