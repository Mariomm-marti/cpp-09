NAME    = btc
CC      = c++
CFLAGS  = -Wall -Werror -Wextra -std=c++98
DEBUG   = -D __CPP09_DEBUG_=true

SRCS    = BitcoinExchange.cpp \
					main.cpp
OBJS    = $(SRCS:.cpp=.opp)
DOBJS   = $(SRCS:.cpp=.oppd)

%.opp: %.cpp
	$(CC) $(CFLAGS) -O3 -c $< -o $@

%.oppd: %.cpp
	$(CC) $(CFLAGS) $(DEBUG) -g3 -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

all: $(NAME)

debug: $(DOBJS)
	$(CC) $(DOBJS) -o $(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(DOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
