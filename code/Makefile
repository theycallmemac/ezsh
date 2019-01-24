PROMPT_SRC = src/prompt.c

PROMPT_OBJ = $(PROMPT_SRC:.c=.o)

PROMPT = prompt

SERVER_SRC = src/ezshServer.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)

SERVER = server

CFLAGS = -W -Wall -Wextra -Wc99-c11-compat -pedantic -std=c99

all:	$(PROMPT) $(SERVER)

$(PROMPT): $(PROMPT_OBJ)
		gcc -o $(PROMPT) $(PROMPT_OBJ)

$(SERVER): $(SERVER_OBJ)
		gcc -o $(SERVER) $(SERVER_OBJ)

clean:
		rm $(PROMPT_OBJ) $(SERVER_OBJ)

.PHONY: all clean

