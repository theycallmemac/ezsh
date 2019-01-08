PROMPT_SRC = src/prompt.c

PROMPT_OBJ = $(PROMPT_SRC:.c=.o)

PROMPT = prompt

CFLAGS = -W -Wall -Wextra -Wc99-c11-compat -pedantic -std=c99

all:	$(PROMPT)

$(PROMPT): $(PROMPT_OBJ)
		gcc -o $(PROMPT) $(PROMPT_OBJ)

clean:
		rm $(PROMPT_OBJ)

.PHONY: all clean

