NAME = client
SERVER = server

CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

SRC_CLIENT = mandatory/helper.c mandatory/client.c 
SRC_SERVER = mandatory/helper.c mandatory/server.c

SRC_CLIENT_BONUS = bonus/helper_bonus.c bonus/client_bonus.c 
SRC_SERVER_BONUS = bonus/helper_bonus.c bonus/server_bonus.c

HEADER = mandatory/minitalk.h
HEADER_BONUS = bonus/minitalk_bonus.h

CC = cc
FLAGS = -Wall -Wextra -Werror
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)

all: $(NAME) $(SERVER)

$(NAME): $(OBJ_CLIENT)
	$(CC) $(FLAGS) $^ -o $@

$(SERVER): $(OBJ_SERVER)
	$(CC) $(FLAGS) $^ -o $@

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS): $(OBJ_CLIENT_BONUS)
	$(CC) $(FLAGS) $^ -o $@

$(SERVER_BONUS): $(OBJ_SERVER_BONUS)
	$(CC) $(FLAGS) $^ -o $@

mandatory/%.o : mandatory/%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

bonus/%.o : bonus/%.c $(HEADER_BONUS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS)

fclean: clean
	rm -f $(NAME) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

re : fclean all

.PHONY: clean
